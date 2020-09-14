/*
 * print.h
 *
 *  Created on: Sep 13, 2020
 *      Author: momcilo
 */

#ifndef PRINT_H_
#define PRINT_H_

#include "img_prep.h"					//loadStatus
#include "img_work.h"					//workDigitStatuses
#include "recognition.h"				//detectedNumber
#include <iostream>						//cout

void writeOutLoadErrors(const loadStatus* retLoadStatus, const cv::String* imageLocation);

void writeOutWorkErrors(const workDigitStatuses* retWorkStatuses, const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3);

void writeOutDetectedErrors(const detectedNumber* retDetectedNumber);

void printOutDigits(const detectedNumber* digits, const bool toWrite);

void printOutFullNumber(const detectedNumber* digits, const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3);

#endif /* PRINT_H_ */
