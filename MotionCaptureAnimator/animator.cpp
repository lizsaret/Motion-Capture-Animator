#include "animator.h"

Animator::Animator(QObject *parent) : QObject(parent)
{

}

/*
    used to rotate an image (based on the angle between two body parts)
    source: https://github.com/milq/cvrotate2D
*/
Mat Animator::rotateImage(Mat src, double degrees)
{
    Mat dst;
    Point2f center(src.cols/2.0, src.rows/2.0);
    Mat rot = cv::getRotationMatrix2D(center, degrees*(-1), 1.0);
    Rect bbox = cv::RotatedRect(center,src.size(), degrees).boundingRect();

    rot.at<double>(0,2) += bbox.width/2.0 - center.x;
    rot.at<double>(1,2) += bbox.height/2.0 - center.y;

    warpAffine(src, dst, rot, bbox.size());
    return dst;
}

/*
    accepts values for new contrast, brightness and saturation
    returns a new photo adjusted based on the inputs given
    ref: https://docs.opencv.org/2.4/doc/tutorials/core/basic_linear_transform/basic_linear_transform.html
*/
Mat Animator::adjustImage(Mat img, double newContrast, double newSaturation, int newBrightness)
{
    if (rotateFrames == true)
        img = rotateImage(img, 270);

    Mat newImg = Mat::zeros(img.size(), img.type());

    // change the brightness and contrast of the image
    for(int y = 1; y < img.rows-1; y++) {
        for(int x = 1; x < img.cols-1; x++) {
            for(int c = 0; c < 3; c++) {
                newImg.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(newContrast*(img.at<Vec3b>(y,x)[c] ) + newBrightness);
            }
        }
    }

    // change the saturatio of the image
    cvtColor(newImg, newImg, CV_BGR2HSV);
    for(int y = 1; y < img.rows-1; y++) {
        for(int x = 1; x < img.cols-1; x++) {
            newImg.at<Vec3b>(y,x)[1] += newSaturation;
        }
    }
    cvtColor(newImg, newImg, CV_HSV2BGR);

    return newImg;
}

/*
    accepts lower and upper hsv thresholds values for colors
    returns the thresholded version of the image based on the color
*/
Mat Animator::thresholdColor(Mat img, Scalar lower, Scalar upper)
{
    Mat imgHSV, imgThreshed;

    int dilation_size = 3;
    Mat dilationElement = getStructuringElement(MORPH_CROSS,
                    Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                    Point(dilation_size, dilation_size) );

    cvtColor(img, imgHSV, CV_BGR2HSV);

    inRange(imgHSV, lower, upper, imgThreshed);

//    erode(imgThreshed, imgThreshed, erosionElement);
    dilate(imgThreshed, imgThreshed, dilationElement);

    imgHSV.release();
    return imgThreshed;
}

/*
    uses blob detection to locate the position of the given color
    returns the point coordinate
    ref: http://www.learnopencv.com/blob-detection-using-opencv-python-c/
*/
Point Animator::locateCoordinate(Mat threshImg)
{
    SimpleBlobDetector::Params params;
    Point newPoint;
    vector<KeyPoint> keypoints;
    Ptr<SimpleBlobDetector> detector;

    params.filterByCircularity = false;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.filterByColor = true;
    params.blobColor = 255;
    // params.filterByArea = true;
    // params.minArea = 30;

    detector = SimpleBlobDetector::create(params);
    detector->detect(threshImg, keypoints);

    // largest blob will be the position of the color
    if (keypoints.size() > 0) {
        float maxArea = -999999;
        for(int i = 0; i < (int)keypoints.size(); i++) {
            if(keypoints.at(i).size >= maxArea){
                // set it as the current position and change value of maxArea
                Point2f point = keypoints.at(i).pt;
                newPoint = Point(point.x, point.y);
                maxArea = keypoints.at(i).size;
            }
        }
    }

    return newPoint;
}

/*
    uses blob detection to locate the position of the given color
    returns two point coordinates
*/
vector<Point> Animator::locateCoordinates(Mat threshImg)
{
    SimpleBlobDetector::Params params;
    Point newPoint1, newPoint2;
    vector<KeyPoint> keypoints;
    vector<Point> twoPoints;
    Ptr<SimpleBlobDetector> detector;

    params.filterByCircularity = false;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.filterByColor = true;
    params.blobColor = 255;

    detector = SimpleBlobDetector::create(params);
    detector->detect(threshImg, keypoints);

    // two largest blobs will be the position of the color
    if (keypoints.size() > 0) {
        float firstMaxArea = -999999;
        float secondMaxArea = -999999;
        for(int i = 0; i < (int)keypoints.size(); i++) {
            if(keypoints.at(i).size >= secondMaxArea) {
                if(keypoints.at(i).size >= firstMaxArea) {
                    Point2f point = keypoints.at(i).pt;

                    newPoint2 = newPoint1;
                    secondMaxArea = firstMaxArea;

                    newPoint1 = Point(point.x, point.y);
                    firstMaxArea = keypoints.at(i).size;
                } else{
                    Point2f point = keypoints.at(i).pt;

                    newPoint2 = Point(point.x, point.y);
                    secondMaxArea = keypoints.at(i).size;
                }
            }
        }
    }

    twoPoints.push_back(newPoint1);
    twoPoints.push_back(newPoint2);

    return twoPoints;
}

/*
    checks if the two given points will overlap (meaining they belong to the same body part)
    returns true or false
*/
bool Animator::isOverlapping(Point currPt, Point otherPt)
{
    int threshValue = 20;
    if  (((currPt.x <= (otherPt.x + threshValue)) && (currPt.x >= (otherPt.x - threshValue)))
            && ((currPt.y <= (otherPt.y + threshValue)) && (currPt.y >= (otherPt.y - threshValue))))
        return true;
    else return false;
}

/*
    scans the given frame and saves the coordinates of the detected body parts
    returns a frame containing different colored points representing the body parts
*/
Mat Animator::postureDetection(Mat img, Pose *currPose)
{
    Mat imgDetected = Mat::zeros(img.size(), CV_8UC3);
    Mat red, blue, yellow, green, purple, pink, orange;
    vector<Point> tempOrg, tempPnk, tempPur, tempGrn;

    red = thresholdColor(img, RED_LOWER_HSV, RED_UPPER_HSV);
    blue = thresholdColor(img, BLUE_LOWER_HSV, BLUE_UPPER_HSV);
    yellow = thresholdColor(img, YELLOW_LOWER_HSV, YELLOW_UPPER_HSV);
    green = thresholdColor(img, GREEN_LOWER_HSV, GREEN_UPPER_HSV);
    purple = thresholdColor(img, PURPLE_LOWER_HSV, PURPLE_UPPER_HSV);
    pink = thresholdColor(img, PINK_LOWER_HSV, PINK_UPPER_HSV);
    orange = thresholdColor(img, ORANGE_LOWER_HSV, ORANGE_UPPER_HSV);

    // change the coordinates of the positions based on the detected thresholds
    if (locateCoordinate(red) != Point(0,0))
        currPose->headPos = locateCoordinate(red);
    if (locateCoordinate(blue) != Point(0,0))
        currPose->neckPos = locateCoordinate(blue);
    if (locateCoordinate(yellow) != Point(0,0))
        currPose->hipsPos = locateCoordinate(yellow);

    // for colors that were used twice, look for the coordinate that has a smaller value of y
    tempOrg = locateCoordinates(orange);
    if ((tempOrg.at(0) != Point(0,0)) && (tempOrg.at(1) != Point(0,0))) {
        if((tempOrg.at(0)).y <= (tempOrg.at(1)).y) {
            currPose->rightelbowPos = tempOrg.at(0);
            currPose->rightkneePos = tempOrg.at(1);
        } else {
            currPose->rightelbowPos = tempOrg.at(1);
            currPose->rightkneePos = tempOrg.at(0);
        }
    } else if ((tempOrg.at(0) == Point(0,0)) && (tempOrg.at(1) != Point(0,0))) {
        if ((tempOrg.at(1)).y <= (orange.rows/3)) currPose->rightelbowPos = tempOrg.at(1);
        else currPose->rightkneePos = tempOrg.at(1);
    } else if ((tempOrg.at(0) != Point(0,0)) && (tempOrg.at(1) == Point(0,0))) {
        if ((tempOrg.at(0)).y <= (orange.rows/3)) currPose->rightelbowPos = tempOrg.at(0);
        else currPose->rightkneePos = tempOrg.at(0);
    }

    tempGrn = locateCoordinates(green);
    if ((tempGrn.at(0) != Point(0,0)) && (tempGrn.at(1) != Point(0,0))) {
        if((tempGrn.at(0)).y <= (tempGrn.at(1)).y) {
            currPose->righthandPos = tempGrn.at(0);
            currPose->rightfootPos = tempGrn.at(1);
        } else {
            currPose->righthandPos = tempGrn.at(1);
            currPose->rightfootPos = tempGrn.at(0);
        }
    } else if ((tempGrn.at(0) == Point(0,0)) && (tempGrn.at(1) != Point(0,0))) {
        if ((tempGrn.at(1)).y <= (green.rows/3)) currPose->righthandPos = tempGrn.at(1);
        else currPose->rightfootPos = tempGrn.at(1);
    } else if ((tempGrn.at(0) != Point(0,0)) && (tempGrn.at(1) == Point(0,0))) {
        if ((tempGrn.at(0)).y <= (green.rows/3)) currPose->righthandPos = tempGrn.at(0);
        else currPose->rightfootPos = tempGrn.at(0);
    }

    tempPnk = locateCoordinates(pink);
    if ((tempPnk.at(0) != Point(0,0)) && (tempPnk.at(1) != Point(0,0))) {
        if((tempPnk.at(0)).y <= (tempPnk.at(1)).y) {
            currPose->leftelbowPos = tempPnk.at(0);
            currPose->leftkneePos = tempPnk.at(1);
        } else {
            currPose->leftelbowPos = tempPnk.at(1);
            currPose->leftkneePos = tempPnk.at(0);
        }
    } else if ((tempPnk.at(0) == Point(0,0)) && (tempPnk.at(1) != Point(0,0))) {
        if ((tempPnk.at(1)).y <= (pink.rows/3)) currPose->leftelbowPos = tempPnk.at(1);
        else currPose->leftkneePos = tempPnk.at(1);
    } else if ((tempPnk.at(0) != Point(0,0)) && (tempPnk.at(1) == Point(0,0))) {
        if ((tempPnk.at(0)).y <= (pink.rows/3)) currPose->leftelbowPos = tempPnk.at(0);
        else currPose->leftkneePos = tempPnk.at(0);
    }

    tempPur = locateCoordinates(purple);
    if ((tempPur.at(0) != Point(0,0)) && (tempPur.at(1) != Point(0,0))) {
        if((tempPur.at(0)).y <= (tempPur.at(1)).y) {
            currPose->lefthandPos = tempPur.at(0);
            currPose->leftfootPos = tempPur.at(1);
        } else {
            currPose->lefthandPos = tempPur.at(1);
            currPose->leftfootPos = tempPur.at(0);
        }
    } else if ((tempPur.at(0) == Point(0,0)) && (tempPur.at(1) != Point(0,0))) {
        if ((tempPur.at(1)).y <= (purple.rows/3)) currPose->lefthandPos = tempPur.at(1);
        else currPose->leftfootPos = tempPur.at(1);
    } else if ((tempPur.at(0) != Point(0,0)) && (tempPur.at(1) == Point(0,0))) {
        if ((tempPur.at(0)).y <= (purple.rows/3)) currPose->lefthandPos = tempPur.at(0);
        else currPose->leftkneePos = tempPur.at(0);
    }

    circle(imgDetected, currPose->headPos, 10, RED_RGB, -1, 8, 0);
    circle(imgDetected, currPose->neckPos, 10, BLUE_RGB, -1, 8, 0);
    circle(imgDetected, currPose->hipsPos, 10, YELLOW_RGB, -1, 8, 0);
    circle(imgDetected, currPose->rightelbowPos, 10, ORANGE1_RGB, -1, 8, 0);
    circle(imgDetected, currPose->rightkneePos, 10, ORANGE2_RGB, -1, 8, 0);
    circle(imgDetected, currPose->righthandPos, 10, GREEN1_RGB, -1, 8, 0);
    circle(imgDetected, currPose->rightfootPos, 10, GREEN2_RGB, -1, 8, 0);
    circle(imgDetected, currPose->leftelbowPos, 10, PINK1_RGB, -1, 8, 0);
    circle(imgDetected, currPose->leftkneePos, 10, PINK2_RGB, -1, 8, 0);
    circle(imgDetected, currPose->lefthandPos, 10, PURPLE1_RGB, -1, 8, 0);
    circle(imgDetected, currPose->leftfootPos, 10, PURPLE2_RGB, -1, 8, 0);

    return imgDetected;
}

/*
    draws a stick figure over the frame containing the endpoints
    returns the stick figure
*/
Mat Animator::connectEndpoints(Mat img, Pose currPose)
{
//    Mat imgSticks(img.rows,img.cols, CV_8UC3, Scalar(0,0,0));
    Mat imgSticks = img;

    // draw the points
    line(imgSticks, currPose.headPos, currPose.neckPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.neckPos, currPose.leftelbowPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.leftelbowPos, currPose.lefthandPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.neckPos, currPose.rightelbowPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.rightelbowPos, currPose.righthandPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.neckPos, currPose.hipsPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.hipsPos, currPose.leftkneePos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.leftkneePos, currPose.leftfootPos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.hipsPos, currPose.rightkneePos, WHITE_RGB, 2, 8, 0);
    line(imgSticks, currPose.rightkneePos, currPose.rightfootPos, WHITE_RGB, 2, 8, 0);

    return imgSticks;
}

/*
    loads the images that will represent the body parts of the character (morty)
*/
void Animator::loadMortyImages()
{    
    QDir tempDir = QDir::current();
    tempDir.cdUp();
    QString currentDir = tempDir.path();
    string pathToFile = currentDir.toUtf8().constData();
    pathToFile.append("/MotionCaptureAnimator/character/");

    headCharacter = imread(pathToFile+"morty/mortyHead.png", IMREAD_UNCHANGED);
    lefthandCharacter = imread(pathToFile+"morty/mortyHandRight.png", IMREAD_UNCHANGED);
    righthandCharacter = imread(pathToFile+"morty/mortyHandLeft.png", IMREAD_UNCHANGED);
    leftarmCharacter = imread(pathToFile+"morty/mortySleeve.png", IMREAD_UNCHANGED);
    rightarmCharacter = imread(pathToFile+"morty/mortySleeve.png", IMREAD_UNCHANGED);
    leftfootCharacter = imread(pathToFile+"morty/mortyShoeRight.png", IMREAD_UNCHANGED);
    rightfootCharacter = imread(pathToFile+"morty/mortyShoeLeft.png", IMREAD_UNCHANGED);

    resize(headCharacter, headCharacter, Size(), 0.45, 0.45);
    resize(lefthandCharacter, lefthandCharacter, Size(), 0.1, 0.1);
    resize(righthandCharacter, righthandCharacter, Size(), 0.1, 0.1)      ;
    resize(leftarmCharacter, leftarmCharacter, Size(), 0.1, 0.1);
    resize(rightarmCharacter, rightarmCharacter, Size(), 0.1, 0.1);
    resize(leftfootCharacter, leftfootCharacter, Size(), 0.1, 0.1);
    resize(rightfootCharacter, rightfootCharacter, Size(), 0.1, 0.1);
}

/*
    loads the images that will represent the body parts of the character (mickey)
*/
void Animator::loadMickeyImages()
{
    QDir tempDir = QDir::current();
    tempDir.cdUp();
    QString currentDir = tempDir.path();
    string pathToFile = currentDir.toUtf8().constData();
    pathToFile.append("/MotionCaptureAnimator/character/mickey/");

    headCharacter = imread(pathToFile+"mickeyHead.png", IMREAD_UNCHANGED);
    lefthandCharacter = imread(pathToFile+"mickeyHand.png", IMREAD_UNCHANGED);
    righthandCharacter = imread(pathToFile+"mickeyHand.png", IMREAD_UNCHANGED);
    leftfootCharacter = imread(pathToFile+"mickeyRightfoot.png", IMREAD_UNCHANGED);
    rightfootCharacter = imread(pathToFile+"mickeyLeftfoot.png", IMREAD_UNCHANGED);
    leftlegCharacter = imread(pathToFile+"mickeyShorts2.png", IMREAD_UNCHANGED);
    rightlegCharacter = imread(pathToFile+"mickeyShorts2.png", IMREAD_UNCHANGED);
    bodyCharacter = imread(pathToFile+"mickeyShorts1.png", IMREAD_UNCHANGED);

    resize(headCharacter, headCharacter, Size(), 0.15, 0.15);
    resize(lefthandCharacter, lefthandCharacter, Size(), 0.08, 0.08);
    resize(righthandCharacter, righthandCharacter, Size(), 0.08, 0.08);
    resize(leftfootCharacter, leftfootCharacter, Size(), 0.08, 0.08);
    resize(rightfootCharacter, rightfootCharacter, Size(), 0.08, 0.08);
    resize(leftlegCharacter, leftlegCharacter, Size(), 0.18, 0.25);
    resize(rightlegCharacter, rightlegCharacter, Size(), 0.18, 0.25);
    resize(bodyCharacter, bodyCharacter, Size(), 0.18, 0.18);
}

/*
    inserts an input png image into the background
    source: http://jepsonsblog.blogspot.be/2012/10/overlay-transparent-image-in-opencv.html
*/
void Animator::overlayImage(Mat background, Mat foreground, Mat output, Point location)
{
  background.copyTo(output);

  // start at the row indicated by location, or at row 0 if location.y is negative.
  for(int y = std::max(location.y , 0); y < background.rows; ++y)
  {
    int fY = y - location.y; // because of the translation

    // we are done of we have processed all rows of the foreground image.
    if(fY >= foreground.rows)
      break;

    // start at the column indicated by location,
    // or at column 0 if location.x is negative.
    for(int x = std::max(location.x, 0); x < background.cols; ++x)
    {
      int fX = x - location.x; // because of the translation.

      // we are done with this row if the column is outside of the foreground image.
      if(fX >= foreground.cols)
        break;

      // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
      double opacity =
        ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])/ 255.;
      // and now combine the background and foreground pixel, using the opacity,
      // but only if opacity > 0.
      for(int c = 0; opacity > 0 && c < output.channels(); ++c)
      {
        unsigned char foregroundPx =
          foreground.data[fY * foreground.step + fX * foreground.channels() + c];
        unsigned char backgroundPx =
          background.data[y * background.step + x * background.channels() + c];
        output.data[y*output.step + output.channels()*x + c] =
          backgroundPx * (1.-opacity) + foregroundPx * opacity;
      }
    }
  }
}

/*
    returns the angle between two points
*/
double Animator::getAngle(Point p1, Point p2)
{
    double angle = atan2(p1.y - p2.y, p1.x - p2.x);
    angle = angle * 180/(3.14);

    return angle+90;
}

/*
    draws the shapes and images representing the body parts of mickey mouse
    returns the frame containing a character
*/
Mat Animator::drawMickey(Mat img, Pose currPose)
{
    Mat imgCharacter(img.rows,img.cols, CV_8UC3, Scalar(255,255,255));
    Mat tempHeadImg, tempLefthandImg, tempRighthandImg, tempLeftfootImg, tempRightfootImg;
    Mat tempShortsbaseImg, tempShortsleftImg, tempShortsrightImg;

    tempHeadImg = rotateImage(headCharacter, getAngle(currPose.headPos, currPose.neckPos));
    tempLefthandImg = rotateImage(lefthandCharacter, getAngle(currPose.leftelbowPos, currPose.lefthandPos));
    tempRighthandImg = rotateImage(righthandCharacter, getAngle(currPose.rightelbowPos, currPose.righthandPos));
    tempLeftfootImg = rotateImage(leftfootCharacter, getAngle(currPose.leftkneePos, currPose.leftfootPos));
    tempRightfootImg = rotateImage(rightfootCharacter, getAngle(currPose.rightkneePos, currPose.rightfootPos));
    tempShortsbaseImg = rotateImage(bodyCharacter, getAngle(currPose.neckPos, currPose.hipsPos));
    tempShortsleftImg = rotateImage(leftlegCharacter, getAngle(currPose.hipsPos, currPose.leftkneePos));
    tempShortsrightImg = rotateImage(rightlegCharacter, getAngle(currPose.hipsPos, currPose.rightkneePos));

    // draw the character using shapes and images
    line(imgCharacter, currPose.neckPos, currPose.hipsPos, BLACK_RGB, 50, 8, 0);
    line(imgCharacter, currPose.headPos, currPose.neckPos, BLACK_RGB, 20, 8, 0);
    line(imgCharacter, currPose.neckPos, currPose.leftelbowPos, BLACK_RGB, 15, 8, 0);
    line(imgCharacter, currPose.neckPos, currPose.rightelbowPos, BLACK_RGB, 15, 8, 0);
    line(imgCharacter, currPose.hipsPos, currPose.leftkneePos, BLACK_RGB, 15, 8, 0);
    line(imgCharacter, currPose.leftkneePos, currPose.leftfootPos, BLACK_RGB, 15, 8, 0);
    line(imgCharacter, currPose.hipsPos, currPose.rightkneePos, BLACK_RGB, 15, 8, 0);
    line(imgCharacter, currPose.rightkneePos, currPose.rightfootPos, BLACK_RGB, 15, 8, 0);

    overlayImage(imgCharacter, tempShortsleftImg, imgCharacter,
                 Point(currPose.hipsPos.x - (tempShortsleftImg.cols/2 - 15), currPose.hipsPos.y - 10));

    overlayImage(imgCharacter, tempShortsrightImg, imgCharacter,
                 Point(currPose.hipsPos.x - (tempShortsrightImg.cols/2 + 15), currPose.hipsPos.y - 10));

    overlayImage(imgCharacter, tempShortsbaseImg, imgCharacter,
                 Point(currPose.hipsPos.x - (tempShortsbaseImg.cols/2), currPose.hipsPos.y - (tempShortsbaseImg.rows/2 - 12)));

    line(imgCharacter, currPose.leftelbowPos, currPose.lefthandPos, BLACK_RGB, 15, 8, 0);
    line(imgCharacter, currPose.rightelbowPos, currPose.righthandPos, BLACK_RGB, 15, 8, 0);

    overlayImage(imgCharacter, tempHeadImg, imgCharacter,
                 Point(currPose.headPos.x - (tempHeadImg.cols/2), currPose.headPos.y - (tempHeadImg.rows/2 - 15)));

    overlayImage(imgCharacter, tempLefthandImg, imgCharacter,
                 Point(currPose.lefthandPos.x - (tempLefthandImg.cols/2), currPose.lefthandPos.y - (tempLefthandImg.rows/2)));

    overlayImage(imgCharacter, tempRighthandImg, imgCharacter,
                 Point(currPose.righthandPos.x - (tempRighthandImg.cols/2), currPose.righthandPos.y - (tempRighthandImg.rows/2)));

    overlayImage(imgCharacter, tempLeftfootImg, imgCharacter,
                 Point(currPose.leftfootPos.x - (tempLeftfootImg.cols/2 - 15), currPose.leftfootPos.y - (tempLeftfootImg.rows/2)));

    overlayImage(imgCharacter, tempRightfootImg, imgCharacter,
                 Point(currPose.rightfootPos.x - (tempRightfootImg.cols/2 + 15), currPose.rightfootPos.y - (tempRightfootImg.rows/2)));

    return imgCharacter;
}


/*
    rotates and draws the images representing the body parts of the subject
    returns the frame containing a character
*/
Mat Animator::drawMorty(Mat img, Pose currPose)
{
    Mat imgCharacter(img.rows,img.cols, CV_8UC3, Scalar(255,255,255));
    Mat tempHeadImg, tempSleeveRight, tempSleeveLeft;
    Mat tempHandRight, tempHandLeft, tempShoeRight, tempShoeLeft;

    // rotate the respective images based on teh position of their endpoints
    tempHeadImg = rotateImage(headCharacter, getAngle(currPose.headPos, currPose.neckPos));
    tempSleeveRight = rotateImage(rightarmCharacter, getAngle(currPose.neckPos, currPose.rightelbowPos));
    tempSleeveLeft = rotateImage(leftarmCharacter, getAngle(currPose.neckPos, currPose.leftelbowPos));
    tempHandRight = rotateImage(righthandCharacter, getAngle(currPose.rightelbowPos, currPose.righthandPos));
    tempHandLeft = rotateImage(lefthandCharacter, getAngle(currPose.leftelbowPos, currPose.lefthandPos));
    tempShoeRight = rotateImage(rightfootCharacter, getAngle(currPose.rightkneePos, currPose.rightfootPos));
    tempShoeLeft = rotateImage(leftfootCharacter, getAngle(currPose.leftkneePos, currPose.leftfootPos));

    // draw the character using shapes and images
    line(imgCharacter, currPose.headPos, currPose.neckPos, FLESH_RGB, 15, 8, 0);
    line(imgCharacter, Point(currPose.neckPos.x + 20, currPose.neckPos.y + 22), currPose.leftelbowPos, FLESH_RGB, 15, 8, 0);
    line(imgCharacter, Point(currPose.neckPos.x - 20, currPose.neckPos.y + 22), currPose.rightelbowPos, FLESH_RGB, 15, 8, 0);
    line(imgCharacter, currPose.leftelbowPos, currPose.lefthandPos, FLESH_RGB, 15, 8, 0);
    line(imgCharacter, currPose.rightelbowPos, currPose.righthandPos, FLESH_RGB, 15, 8, 0);

    overlayImage(imgCharacter, tempSleeveRight, imgCharacter,
                 Point(currPose.neckPos.x - (tempSleeveRight.cols/2 + 20), currPose.neckPos.y));

    overlayImage(imgCharacter, tempSleeveLeft, imgCharacter,
                 Point(currPose.neckPos.x - (tempSleeveLeft.cols/2 - 20), currPose.neckPos.y));

    overlayImage(imgCharacter, tempHandRight, imgCharacter,
                 Point(currPose.righthandPos.x - (tempHandRight.cols/2), currPose.righthandPos.y - (tempHandRight.rows/2)));

    overlayImage(imgCharacter, tempHandLeft, imgCharacter,
                 Point(currPose.lefthandPos.x - (tempHandLeft.cols/2), currPose.lefthandPos.y - (tempHandLeft.rows/2)));

    line(imgCharacter, currPose.hipsPos, currPose.leftkneePos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.leftkneePos, currPose.leftfootPos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.hipsPos, currPose.rightkneePos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.rightkneePos, currPose.rightfootPos, BLUE_RGB, 15, 8, 0);

    overlayImage(imgCharacter, tempShoeRight, imgCharacter,
                 Point(currPose.rightfootPos.x - (tempShoeRight.cols/2), currPose.rightfootPos.y - (tempShoeRight.rows/2)));

    overlayImage(imgCharacter, tempShoeLeft, imgCharacter,
                 Point(currPose.leftfootPos.x - (tempShoeLeft.cols/2), currPose.leftfootPos.y - (tempShoeLeft.rows/2)));
    line(imgCharacter, currPose.neckPos, currPose.hipsPos, YELLOW_RGB, 50, 8, 0);


    overlayImage(imgCharacter, tempHeadImg, imgCharacter,
                 Point(currPose.headPos.x - (tempHeadImg.cols/2), currPose.headPos.y - (tempHeadImg.rows/2 - 15)));

    return imgCharacter;
}

/*
    draws the shapes representing the body parts of the subject
    returns the frame containing a character
*/
Mat Animator::drawShapes(Mat img, Pose currPose)

{
    Mat imgCharacter(img.rows,img.cols, CV_8UC3, Scalar(255,255,255));

    line(imgCharacter, currPose.headPos, currPose.neckPos, YELLOW_RGB, 20, 8, 0);
    line(imgCharacter, currPose.neckPos, currPose.leftelbowPos, YELLOW_RGB, 15, 8, 0);
    line(imgCharacter, currPose.leftelbowPos, currPose.lefthandPos, YELLOW_RGB, 15, 8, 0);
    line(imgCharacter, currPose.neckPos, currPose.rightelbowPos, YELLOW_RGB, 15, 8, 0);
    line(imgCharacter, currPose.rightelbowPos, currPose.righthandPos, YELLOW_RGB, 15, 8, 0);
    line(imgCharacter, currPose.hipsPos, currPose.leftkneePos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.leftkneePos, currPose.leftfootPos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.hipsPos, currPose.rightkneePos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.rightkneePos, currPose.rightfootPos, BLUE_RGB, 15, 8, 0);
    line(imgCharacter, currPose.neckPos, currPose.hipsPos, RED_RGB, 15, 8, 0);
    rectangle(imgCharacter, currPose.neckPos, currPose.hipsPos, RED_RGB, 50, 8, 0);
    circle(imgCharacter, currPose.headPos, 30, YELLOW_RGB, -1, 8, 0);

    return imgCharacter;
}
