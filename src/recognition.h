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
int countInArea(const Mat* inputDigit, Point p1, Point p2);

//detects presence of 0
void detect0(const Mat* digit);

//detects presence of 1
void detect1(const Mat* digit);

//detects presence of 2
void detect2(const Mat* digit);

//detects presence of 3
void detect3(const Mat* digit);

//detects presence of 4
void detect4(const Mat* digit);

//detects presence of 5
void detect5(const Mat* digit);

//detects presence of 6
void detect6(const Mat* digit);

//detects presence of 7
void detect7(const Mat* digit);

//detects presence of 8
void detect8(const Mat* digit);

//detects presence of 9
void detect9(const Mat* digit);

//detects given numbers
void numbersToDetect(const Mat* digit);

//writes out detected digit and returns its int value
int getDetectedDigit();

//detects digits if they exist and returns the number they make
int detectNumbers(const Mat* digit1, const Mat* digit2, const Mat* digit3);

#endif /* RECOGNITION_H_ */
