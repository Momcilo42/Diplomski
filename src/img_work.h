/*
 * img_work.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef IMG_WORK_H_
#define IMG_WORK_H_

#include "opencv2/core.hpp"				//Mat

//crops out almost empty space around digit
void cropOutAlmostEmpty(cv::Mat* img);

//crops out almost empty space around leftmost 1
void cropOutAlmostEmpty1(cv::Mat* img);

//crops out almost empty space around rightmost 0
void cropOutAlmostEmpty0(cv::Mat* img);

//detects inner edge of surrounding circle at given ratio of height
std::pair<int,int>  innerCircleLeftRightEdgeDetection(const cv::Mat* in, float ratio);

//checks the horizontal line at given ratio of height for intersecting lines
std::vector<int> horizontalScan(const cv::Mat* in, float ratio);

//checks the vertical line at given ratio of width for intersecting lines
std::vector<int> verticalScan(const cv::Mat* in, float ratio);

//returns position of empty line in the first slot if it detects a two digit number
//returns positions of empty lines if it detects a three digit number
//returns -1 in bits slots to signal an error
std::pair<int,int> getLinesBetweenDigits(const cv::Mat* in);

//removes the parts of the image above and below the digits
void cutOffImageAboveAndBelowTheNumbers(cv::Mat* srcImage);

//returns detected digits
int getDigits(cv::Mat* srcImage, cv::Mat* digit1, cv::Mat* digit2, cv::Mat* digit3);

#endif /* IMG_WORK_H_ */
