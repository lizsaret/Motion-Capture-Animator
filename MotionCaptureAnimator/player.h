#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QDir>
#include <global.h>
#include <animator.h>

using namespace cv;
using namespace std;

class Player : public QThread
{
    Q_OBJECT

signals:
    void outputsReady();
    void outputFramesToWindow(const QImage &image1, const QImage &image2, const QImage &image3);
    void endOfVideo();

protected:
    void run();
    void msleep(int ms);

public:
    Player(QObject *parent = 0);
    ~Player();
    // Load a video from memory
    bool loadVideo(String filename);
    // function that will handle the processing and writing of video
    void processVideo();
    // used to open the videos that were written
    void openVids();
    // Play the video
    void play();
    // Stop/pause the video
    void stopVideo();
    // set value of ready
    void setReady(bool value);
    // check if the Player has been stopped
    bool isStopped() const;
    // check if the outputs are ready
    bool isReady() const;

private:
    QMutex mutex;
    QWaitCondition condition;
    Size frameSize;
    Size reverseFrameSize;
    struct Pose positions;
    Animator* animator;
    int frameRate;
    bool stop;
    bool ready;
    VideoCapture capture;
    VideoCapture cap_sticks;
    VideoCapture cap_shapes;
    VideoCapture cap_adjstd;
    VideoWriter out_sticks;
    VideoWriter out_shapes;
    VideoWriter out_adjstd;
    Mat frameCapture;
    Mat frameAdjstd;
    Mat frameSticks;
    Mat frameShapes;
    Mat rgbFrame1;
    Mat rgbFrame2;
    Mat rgbFrame3;
    Mat adjustedImage;
    Mat drawPoints;
    Mat drawLines;
    Mat drawShapes;
    Mat drawObjects;
    QImage imgInput;
    QImage imgSticks;
    QImage imgShapes;
};

#endif // PLAYER_H
