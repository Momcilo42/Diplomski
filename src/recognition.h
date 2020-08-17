/*
 * recognition.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef RECOGNITION_H_
#define RECOGNITION_H_

#include "opencv_dependencies.h"

//counts non black pixels in given area
int countInArea(Mat inputDigit, Mat tmp, Point p1, Point p2);

//detects presence of 0
void detect0(Mat digit);

//detects presence of 1
void detect1(Mat digit);

//detects presence of 2
void detect2(Mat digit);

//detects presence of 3
void detect3(Mat digit);

//detects presence of 4
void detect4(Mat digit);

//detects presence of 5
void detect5(Mat digit);

//detects presence of 6
void detect6(Mat digit);

//detects presence of 7
void detect7(Mat digit);

//detects presence of 8
void detect8(Mat digit);

//detects presence of 9
void detect9(Mat digit);

//detects given numbers
void numbersToDetect(Mat digit);

//detects digits if they exist
void detectNumbers(Mat digit1, Mat digit2, Mat digit3);

#endif /* RECOGNITION_H_ */
