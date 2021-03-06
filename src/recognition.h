/*
 * recognition.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef RECOGNITION_H_
#define RECOGNITION_H_

#include "opencv2/core.hpp"				//Mat

enum detectionStatus{
	NO_NUMBER_DETECTED = -1,
	NUMBER_DETECTED = -2,
	MULTIPLE_NUMBERS_DETECTED = -3
};

struct detectedDigit{
	detectionStatus status;
	int number;
};

struct detectedNumber{
	detectedDigit digit1;
	detectedDigit digit2;
	detectedDigit digit3;
};

//counts non black pixels in given area
int countInArea(const cv::Mat* inputDigit, cv::Point p1, cv::Point p2);

//detects presence of 0
detectionStatus detect0(const cv::Mat* digit);

//detects presence of 1
detectionStatus detect1(const cv::Mat* digit);

//detects presence of 2
detectionStatus detect2(const cv::Mat* digit);

//detects presence of 3
detectionStatus detect3(const cv::Mat* digit);

//detects presence of 4
detectionStatus detect4(const cv::Mat* digit);

//detects presence of 5
detectionStatus detect5(const cv::Mat* digit);

//detects presence of 6
detectionStatus detect6(const cv::Mat* digit);

//detects presence of 7
detectionStatus detect7(const cv::Mat* digit);

//detects presence of 8
detectionStatus detect8(const cv::Mat* digit);

//detects presence of 9
detectionStatus detect9(const cv::Mat* digit);

//detects digit, writes it out and returns its int value
detectedDigit detectDigit(const cv::Mat* digit);

//detects digits if they exist and returns the number they make
detectedNumber detectNumbers(const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3);

#endif /* RECOGNITION_H_ */
