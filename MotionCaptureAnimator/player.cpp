#include "player.h"

Player::Player(QObject *parent) : QThread(parent)
{
    stop = true;
    ready = false;
    animator = new Animator();
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

/*
    opens the file chosen by the user
*/
bool Player::loadVideo(String filename)
{
    capture.open(filename);
    if (capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        frameSize = Size(capture.get(CV_CAP_PROP_FRAME_WIDTH)*.25, capture.get(CV_CAP_PROP_FRAME_HEIGHT)*.25);
        reverseFrameSize = Size(capture.get(CV_CAP_PROP_FRAME_HEIGHT)*.25, capture.get(CV_CAP_PROP_FRAME_WIDTH)*.25);

        ready = false;

        return true;
    }
    else
        return false;
}

void Player::play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

/*
    animates opened input video and writes the files into memory
*/
void Player::processVideo()
{
    if (rotateFrames == true) {
        out_adjstd = VideoWriter("out_adjstd.avi", CV_FOURCC('X','V','I','D'), 20, reverseFrameSize);
        out_sticks = VideoWriter("out_sticks.avi", CV_FOURCC('X','V','I','D'), 20, reverseFrameSize);
        out_shapes = VideoWriter("out_shapes.avi", CV_FOURCC('X','V','I','D'), 20, reverseFrameSize);
    } else {
        out_adjstd = VideoWriter("out_adjstd.avi", CV_FOURCC('X','V','I','D'), 20, frameSize);
        out_sticks = VideoWriter("out_sticks.avi", CV_FOURCC('X','V','I','D'), 20, frameSize);
        out_shapes = VideoWriter("out_shapes.avi", CV_FOURCC('X','V','I','D'), 20, frameSize);
    }

    if (characterChoice == 1)
        animator->loadMickeyImages();
    else if (characterChoice ==2)
        animator->loadMortyImages();
    while(true){
        if (!capture.read(frameCapture))
        {
            break;
        }

        if (frameCapture.empty()) {
            break;
        }
        resize(frameCapture, adjustedImage, Size(), 0.25, 0.25);

        adjustedImage = animator->adjustImage(adjustedImage, contrastVal, saturationVal, brightnessVal);
        drawPoints = animator->postureDetection(adjustedImage, &positions);
        drawLines = animator->connectEndpoints(drawPoints, positions);

        if (characterChoice == 0)
            drawShapes = animator->drawShapes(drawPoints, positions);
        else if (characterChoice == 1)
            drawShapes = animator->drawMickey(drawPoints, positions);
        else if (characterChoice == 2)
            drawShapes = animator->drawMorty(drawPoints, positions);

        out_adjstd.write(adjustedImage);
        out_sticks.write(drawLines);
        out_shapes.write(drawShapes);
    }
    capture.set(CAP_PROP_POS_MSEC, 0);
}

/*
    opens the three output videos written by processVideo()
    signals outputsReady() to start the videos in window
*/
void Player::openVids()
{
    cap_adjstd.open("out_adjstd.avi");
    cap_sticks.open("out_sticks.avi");
    cap_shapes.open("out_shapes.avi");

    frameRate = (int) cap_adjstd.get(CV_CAP_PROP_FPS);
}

void Player::run()
{
    if (ready == false) {
//        QElapsedTimer timer;
//        timer.start();
        processVideo();
        openVids();
        ready = true;
//        cout << "Processing and writing took " << timer.elapsed() << " milliseconds\n";
        emit outputsReady();
    }
    int delay = (1000/frameRate);
    while (!stop) {
        if ((!cap_adjstd.read(frameAdjstd) || !cap_sticks.read(frameSticks)) || !cap_shapes.read(frameShapes)) {
            stop = true;
        }
        if ((frameAdjstd.empty() || frameSticks.empty()) || frameShapes.empty()) {
            stop = true;
            out_adjstd.release();
            out_sticks.release();
            out_shapes.release();

            cap_adjstd.release();
            cap_sticks.release();
            cap_shapes.release();
            emit endOfVideo();
        }

        // converting input frame to QImage
        if (frameAdjstd.channels()== 3){
            cv::cvtColor(frameAdjstd, rgbFrame1, CV_BGR2RGB);
            imgInput = QImage((const unsigned char*)(rgbFrame1.data),
                              rgbFrame1.cols,rgbFrame1.rows,QImage::Format_RGB888);
        }
        else
        {
            imgInput = QImage((const unsigned char*)(frameAdjstd.data),
                              frameAdjstd.cols,frameAdjstd.rows,QImage::Format_Indexed8);
        }

        // converting sticks frame to QImage
        if (frameSticks.channels()== 3){
            cv::cvtColor(frameSticks, rgbFrame2, CV_BGR2RGB);
            imgSticks = QImage((const unsigned char*)(rgbFrame2.data),
                               rgbFrame2.cols,rgbFrame2.rows,QImage::Format_RGB888);
        }
        else
        {
            imgSticks = QImage((const unsigned char*)(frameSticks.data),
                               frameSticks.cols,frameSticks.rows,QImage::Format_Indexed8);
        }

        // converting shapes frame to QImage
        if (frameShapes.channels()== 3){
            cv::cvtColor(frameShapes, rgbFrame3, CV_BGR2RGB);
            imgShapes = QImage((const unsigned char*)(rgbFrame3.data),
                               rgbFrame3.cols,rgbFrame3.rows,QImage::Format_RGB888);
        }
        else
        {
            imgShapes = QImage((const unsigned char*)(frameShapes.data),
                               frameShapes.cols,frameShapes.rows,QImage::Format_Indexed8);
        }

        emit outputFramesToWindow(imgInput, imgSticks, imgShapes);
        this->msleep(delay);
    }
}

void Player::setReady(bool value) {
    ready = value;
}

void Player::stopVideo()
{
    stop = true;
}

bool Player::isStopped() const
{
    return this->stop;
}

bool Player::isReady() const
{
    return this->ready;
}


