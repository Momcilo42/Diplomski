/*
 * tests.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef TESTS_H_
#define TESTS_H_

#include "img_prep.h"
#include "img_work.h"
#include "recognition.h"

//tests lines going through the image
void testScan(cv::Mat in);

//tests selected lines to see where 30s fit in
void test30Lines(cv::Mat in);

//tests selected lines to see where 60s fit in
void test60Lines(cv::Mat in);

//tests selected lines to see where 80s fit in
void test80Lines(cv::Mat in);

//selects functions to test
int testSelectedFunctions(cv::Mat* inp, cv::Mat* num1, cv::Mat* num2, cv::Mat* num3);

//tests 65 preselected images to speed up testing
void testAll(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3);

#endif /* TESTS_H_ */
