/*
 * img_work.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef IMG_WORK_H_
#define IMG_WORK_H_

#include "opencv_dependencies.h"

//crops out almost empty space around digit
void cropOutAlmostEmpty(Mat* img);

//crops out almost empty space around leftmost 1
void cropOutAlmostEmpty1(Mat* img);

//crops out almost empty space around rightmost 0
void cropOutAlmostEmpty0(Mat* img);

//detects inner edge of surrounding circle at given ratio of height
Point innerCircleH(Mat in, float ratio);

//detects inner edge of surrounding circle at given ratio of width
Point innerCircleV(Mat in, float ratio);

//checks the horizontal line at given ratio of height for intersecting lines
vector<int> horizontalScan(Mat in, float ratio);

//checks the vertical line at given ratio of width for intersecting lines
vector<int> verticalScan(Mat in, float ratio);

//returns if there are two or more digits
int getNumberOfDigits(Mat in);

//returns the location of the central line going between two digits in two digit number
int getCentralLine(Mat in, int start, int end);

//returns the locations of the central lines going between two digits in three digit number
Point getCentralLines(Mat in);

//removes the parts of the image above and below the digits
void isolateNumbersV(Mat* srcImage);

//returns detected digits
void getNumbers(Mat srcImage, Mat* digit1, Mat* digit2, Mat* digit3);

#endif /* IMG_WORK_H_ */
