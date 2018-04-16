#include "global.h"

using namespace cv;

// Initial HSV thresholds
Scalar RED_LOWER_HSV = Scalar(170, 130, 100);
Scalar RED_UPPER_HSV = Scalar(179, 255, 255);
Scalar BLUE_LOWER_HSV = Scalar(78, 140, 100);
Scalar BLUE_UPPER_HSV = Scalar(110, 255, 255);
Scalar YELLOW_LOWER_HSV = Scalar(20, 100, 100);
Scalar YELLOW_UPPER_HSV = Scalar(60, 255, 255);
Scalar GREEN_LOWER_HSV = Scalar(45, 100, 50);
Scalar GREEN_UPPER_HSV = Scalar(75, 255, 255);
Scalar PURPLE_LOWER_HSV = Scalar(120, 100, 50);
Scalar PURPLE_UPPER_HSV = Scalar(170, 255, 180);
Scalar ORANGE_LOWER_HSV = Scalar(0, 130, 150);
Scalar ORANGE_UPPER_HSV = Scalar(15, 255, 255);
Scalar PINK_LOWER_HSV = Scalar(145, 40, 70);
Scalar PINK_UPPER_HSV = Scalar(170, 135, 255);

// RGB values for color representations
Scalar RED_RGB = Scalar(0, 0, 255);
Scalar BLUE_RGB = Scalar(255, 0, 0);
Scalar YELLOW_RGB = Scalar(0, 255, 255);
Scalar GREEN1_RGB = Scalar(0, 255, 0);
Scalar GREEN2_RGB = Scalar(0, 102, 0);
Scalar PURPLE1_RGB = Scalar(127, 0, 127);
Scalar PURPLE2_RGB = Scalar(255, 0, 127);
Scalar ORANGE1_RGB = Scalar(0, 165, 255);
Scalar ORANGE2_RGB = Scalar(0, 100 ,255);
Scalar PINK1_RGB = Scalar(203, 192, 255);
Scalar PINK2_RGB = Scalar(153, 153, 255);
Scalar WHITE_RGB = Scalar(255, 255, 255);
Scalar BLACK_RGB = Scalar(0, 0, 0);
Scalar FLESH_RGB = Scalar(156, 186, 230);

// values used for adjusting input video
double contrastVal = 1;
double saturationVal = 1;
int brightnessVal = 5;

int characterChoice = 1;

bool rotateFrames = false;
