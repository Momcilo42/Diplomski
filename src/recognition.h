/*
 * recognition.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef RECOGNITION_H_
#define RECOGNITION_H_

#include "opencv2/core.hpp"				//Mat

//counts non black pixels in given area
int countInArea(const cv::Mat* inputDigit, cv::Point p1, cv::Point p2);

//detects presence of 0
int detect0(const cv::Mat* digit);

//detects presence of 1
int detect1(const cv::Mat* digit);

//detects presence of 2
int detect2(const cv::Mat* digit);

//detects presence of 3
int detect3(const cv::Mat* digit);

//detects presence of 4
int detect4(const cv::Mat* digit);

//detects presence of 5
int detect5(const cv::Mat* digit);

//detects presence of 6
int detect6(const cv::Mat* digit);

//detects presence of 7
int detect7(const cv::Mat* digit);

//detects presence of 8
int detect8(const cv::Mat* digit);

//detects presence of 9
int detect9(const cv::Mat* digit);

//detects digit, writes it out and returns its int value
int detectDigit(const cv::Mat* digit);

//detects digits if they exist and returns the number they make
int detectNumbers(const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3);

#endif /* RECOGNITION_H_ */
