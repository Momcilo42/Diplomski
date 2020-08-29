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
std::pair<int,int>  innerCircleH(const Mat* in, float ratio);

//detects inner edge of surrounding circle at given ratio of width
std::pair<int,int>  innerCircleV(const Mat* in, float ratio);

//checks the horizontal line at given ratio of height for intersecting lines
vector<int> horizontalScan(const Mat* in, float ratio);

//checks the vertical line at given ratio of width for intersecting lines
vector<int> verticalScan(const Mat* in, float ratio);

//returns the location of the central line going between two digits in two digit number
int getCentralLine(const Mat* in, int start, int end);

//returns position of empty line in the first slot if it detects a two digit number
//returns positions of empty lines if it detects a three digit number
//returns -1 in bits slots to signal an error
std::pair<int,int> getLinesBetweenDigits(const Mat* in);

//removes the parts of the image above and below the digits
void isolateNumbersV(Mat* srcImage);

//returns detected digits
int getNumbers(Mat* srcImage, Mat* digit1, Mat* digit2, Mat* digit3);

#endif /* IMG_WORK_H_ */
