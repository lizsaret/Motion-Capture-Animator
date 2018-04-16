#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <QObject>
#include <QDir>
#include <QString>
#include <vector>
#include <iostream>
#include <global.h>

using namespace cv;
using namespace std;

class Animator : QObject
{
    Q_OBJECT
public:
    explicit Animator(QObject *parent = nullptr);

    // adjusts the contrast, saturation and brightness of the frame
    Mat adjustImage(Mat img, double newContrast, double newSaturation, int newBrightness);

    // look for the coordinates of given colors and store them in their proper positions
    Mat postureDetection(Mat img, struct Pose *currPose);
    Mat thresholdColor(Mat img, Scalar lower, Scalar upper);
    Point locateCoordinate(Mat threshImg);
    vector<Point> locateCoordinates(Mat threshImg);
    bool isOverlapping(Point currPt, Point otherPt);


    // used draw shapes that will help in the visualization of the subject's posture
    void loadMortyImages();
    void loadMickeyImages();
    void loadMeeseeksImages();
    void overlayImage(Mat background, Mat foreground, Mat output, Point location);
    double getAngle(Point p1, Point p2);
    Mat rotateImage(Mat src, double degrees);
    Mat connectEndpoints(Mat img, struct Pose currPose);
    Mat drawShapes(Mat img, struct Pose currPose);
    Mat drawMorty(Mat img, struct Pose currPose);
    Mat drawMickey(Mat img, struct Pose currPose);
    Mat drawMeeseeks(Mat img, struct Pose currPose);

private:
    Mat headCharacter;
    Mat lefthandCharacter;
    Mat righthandCharacter;
    Mat leftarmCharacter;
    Mat rightarmCharacter;
    Mat bodyCharacter;
    Mat leftlegCharacter;
    Mat rightlegCharacter;
    Mat leftfootCharacter;
    Mat rightfootCharacter;
};

#endif // ANIMATOR_H
