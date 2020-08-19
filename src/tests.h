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
#include "opencv_dependencies.h"
#include "recognition.h"

//#include "znakovi.cpp"

//tests lines going through the image
void testScan(Mat in);

//tests selected lines to see where 30s fit in
void test30Lines(Mat in);

//tests selected lines to see where 60s fit in
void test60Lines(Mat in);

//tests selected lines to see where 80s fit in
void test80Lines(Mat in);

//selects functions to test
void testSelectedFunctions(Mat* inp, Mat* num1, Mat* num2, Mat* num3);

//tests 65 preselected images to speed up testing
void testAll(Mat* num1, Mat* num2, Mat* num3);

#endif /* TESTS_H_ */
