#ifndef GLOBAL_H
#define GLOBAL_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

struct Pose {
    Point headPos;
    Point neckPos;
    Point hipsPos;
    Point lefthandPos;
    Point righthandPos;
    Point leftfootPos;
    Point rightfootPos;
    Point leftelbowPos;
    Point rightelbowPos;
    Point leftkneePos;
    Point rightkneePos;
};
/*
    Note the color-body equivalence:
    RED 	:	HEAD
    BLUE  	:	NECK
    YELLOW 	:	HIPS
    GREEN 	:	RIGHT HAND
                RIGHT FOOT
    ORANGE	:	RIGHT ELBOW
                RIGHT KNEE
    PURPLE 	:	LEFT HAND
                LEFT FOOT
    PINK 	:	LEFT ELBOW
                LEFT KNEE
*/

// Initial HSV thresholds
extern Scalar RED_LOWER_HSV;
extern Scalar RED_UPPER_HSV;
extern Scalar BLUE_LOWER_HSV;
extern Scalar BLUE_UPPER_HSV;
extern Scalar YELLOW_LOWER_HSV;
extern Scalar YELLOW_UPPER_HSV;
extern Scalar GREEN_LOWER_HSV;
extern Scalar GREEN_UPPER_HSV;
extern Scalar PURPLE_LOWER_HSV;
extern Scalar PURPLE_UPPER_HSV;
extern Scalar ORANGE_LOWER_HSV;
extern Scalar ORANGE_UPPER_HSV;
extern Scalar PINK_LOWER_HSV;
extern Scalar PINK_UPPER_HSV;

// RGB values for color representations
extern Scalar RED_RGB;
extern Scalar BLUE_RGB;
extern Scalar YELLOW_RGB;
extern Scalar GREEN1_RGB;
extern Scalar GREEN2_RGB;
extern Scalar PURPLE1_RGB;
extern Scalar PURPLE2_RGB;
extern Scalar ORANGE1_RGB;
extern Scalar ORANGE2_RGB;
extern Scalar PINK1_RGB;
extern Scalar PINK2_RGB;
extern Scalar WHITE_RGB;
extern Scalar BLACK_RGB;
extern Scalar FLESH_RGB;

// values for adjustment of video
extern double contrastVal;
extern double saturationVal;
extern int brightnessVal;

// integers represent the different characters avaialable
extern int characterChoice;

extern bool rotateFrames;

#endif // GLOBAL_H
