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
Point innerCircleH(const Mat* in, float ratio);

//detects inner edge of surrounding circle at given ratio of width
Point innerCircleV(const Mat* in, float ratio);

//checks the horizontal line at given ratio of height for intersecting lines
vector<int> horizontalScan(const Mat* in, float ratio);

//checks the vertical line at given ratio of width for intersecting lines
vector<int> verticalScan(const Mat* in, float ratio);

//returns if there are two or more digits
int getNumberOfDigits(const Mat* in);

//returns the location of the central line going between two digits in two digit number
int getCentralLine(const Mat* in, int start, int end);

//returns the locations of the central lines going between two digits in three digit number
Point getCentralLines(const Mat* in);

//removes the parts of the image above and below the digits
void isolateNumbersV(Mat* srcImage);

//returns detected digits
int getNumbers(Mat* srcImage, Mat* digit1, Mat* digit2, Mat* digit3);

#endif /* IMG_WORK_H_ */
