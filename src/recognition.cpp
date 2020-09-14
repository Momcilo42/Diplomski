/*
 * recognition.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "recognition.h"


static int digitToDetect = 0;

static const int firstDigitOfTwoDigitNumber = -1;
static const int secondDigitOfTwoDigitNumber = -2;
static const int firstDigitOfThreeDigitNumber = 1;
static const int secondDigitOfThreeDigitNumber = 2;
static const int thirdDigitOfThreeDigitNumber = 3;

static const float threshold1 = 2.45;

int countInArea(const cv::Mat* inputDigit, cv::Point p1, cv::Point p2)
{
	cv::Rect mask(p1, p2);
	cv::Mat cropped(*inputDigit,mask);
	return cv::countNonZero(cropped);;
}

detectionStatus detect0(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 0
	}

	int uArea = countInArea(digit, cv::Point(digit->cols*0.40, 0), cv::Point(digit->cols*0.60, digit->rows*0.3));
	int dArea = countInArea(digit, cv::Point(digit->cols*0.40, digit->rows*0.70), cv::Point(digit->cols*0.60, digit->rows));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.40), cv::Point(digit->cols*0.12, digit->rows*0.60));
	int rArea = countInArea(digit, cv::Point(digit->cols*0.77, digit->rows*0.65), cv::Point(digit->cols, digit->rows*0.35));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.46, digit->rows*0.30), cv::Point(digit->cols*0.54, digit->rows*0.65));

	if(uArea && dArea && lArea && rArea && !cArea)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect1(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NUMBER_DETECTED;
	}

	int dlArea = countInArea(digit, cv::Point(0, digit->rows*0.55), cv::Point(digit->cols*0.41, digit->rows*0.89));
	int drArea = countInArea(digit, cv::Point(digit->cols*0.58, digit->rows*0.7), cv::Point(digit->cols, digit->rows*0.8));
	int ulArea = countInArea(digit, cv::Point(0, 0), cv::Point(digit->cols*0.15, digit->rows*0.30));
	int urArea = countInArea(digit, cv::Point(digit->cols, 0), cv::Point(digit->cols*0.96, digit->rows*0.30));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.35), cv::Point(digit->cols*0.15, digit->rows*0.65));
	int rArea = countInArea(digit, cv::Point(digit->cols, digit->rows*0.35), cv::Point(digit->cols*0.96, digit->rows*0.65));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.35, digit->rows*0.35), cv::Point(digit->cols*0.65, digit->rows*0.65));

	if(!dlArea || (drArea && ulArea && !urArea && !lArea && !rArea && cArea))
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect2(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED; //Number to tall to be 2
	}

	int uArea = countInArea(digit, cv::Point(digit->cols*0.43, 0), cv::Point(digit->cols*0.57, digit->rows*0.3));
	int dArea = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.70), cv::Point(digit->cols*0.57, digit->rows));
	int drArea1 = countInArea(digit, cv::Point(digit->cols*0.76, digit->rows*0.73), cv::Point(digit->cols, digit->rows*0.75));
	int drArea2 = countInArea(digit, cv::Point(digit->cols*0.8, digit->rows*0.80), cv::Point(digit->cols, digit->rows));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.43), cv::Point(digit->cols*0.07, digit->rows*0.57));
	int rArea = countInArea(digit, cv::Point(digit->cols, digit->rows*0.2), cv::Point(digit->cols*0.97, digit->rows*0.65));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.35), cv::Point(digit->cols*0.57, digit->rows*0.65));

	if(uArea && dArea && !lArea && rArea && cArea && !drArea1 && drArea2)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect3(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED; //Number to tall to be 3
	}

	int uArea = countInArea(digit, cv::Point(digit->cols*0.43, 0), cv::Point(digit->cols*0.57, digit->rows*0.3));
	int urArea = countInArea(digit, cv::Point(digit->cols*0.63, digit->rows*0.29), cv::Point(digit->cols, digit->rows*0.30));
	int ulArea = countInArea(digit, cv::Point(digit->cols*0.10, digit->rows*0.15), cv::Point(digit->cols*0.30, digit->rows*0.35));
	int dArea = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.70), cv::Point(digit->cols*0.57, digit->rows));
	int dlArea = countInArea(digit, cv::Point(digit->cols*0.27, digit->rows*0.73), cv::Point(0, digit->rows*0.79));
	int dr1Area = countInArea(digit, cv::Point(digit->cols*0.76, digit->rows*0.73), cv::Point(digit->cols, digit->rows*0.75));
	int dr2Area = countInArea(digit, cv::Point(digit->cols*0.78, digit->rows*0.78), cv::Point(digit->cols, digit->rows));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.43), cv::Point(digit->cols*0.12, digit->rows*0.57));
	int rArea = countInArea(digit, cv::Point(digit->cols, digit->rows*0.35), cv::Point(digit->cols*0.93, digit->rows*0.65));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.45, digit->rows*0.35), cv::Point(digit->cols*0.55, digit->rows*0.65));

	if(uArea && urArea && ulArea && dArea && dlArea && dr1Area && dr2Area && !lArea && rArea && cArea)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect4(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 4
	}

	int ulArea = countInArea(digit, cv::Point(digit->cols*0.20, 0), cv::Point(digit->cols*0.25, digit->rows*0.25));
	int urArea = countInArea(digit, cv::Point(digit->cols, 0), cv::Point(digit->cols*0.91, digit->rows*0.60));
	int c1Area = countInArea(digit, cv::Point(digit->cols*0.49, digit->rows*0.53), cv::Point(digit->cols*0.55, digit->rows*0.60));
	int c2Area = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.62), cv::Point(digit->cols*0.55, digit->rows*0.72));

	if(!ulArea && !urArea && (!c1Area || !c2Area))
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect5(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 5
	}

	int cArea = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.35), cv::Point(digit->cols*0.57, digit->rows*0.65));
	int urArea = countInArea(digit, cv::Point(digit->cols*0.63, digit->rows*0.25), cv::Point(digit->cols, digit->rows*0.26));
	int dlArea = countInArea(digit, cv::Point(0, digit->rows*0.63), cv::Point(digit->cols*0.37, digit->rows*0.65));

	if(cArea && !dlArea && !urArea)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect6(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 6
	}

	int ulArea = countInArea(digit, cv::Point(0, 0), cv::Point(digit->cols*0.35, digit->rows*0.30));
	int urArea = countInArea(digit, cv::Point(digit->cols*0.65, digit->rows*0.30), cv::Point(digit->cols, digit->rows*0.32));
	int dl1Area = countInArea(digit, cv::Point(0, digit->rows*0.65), cv::Point(digit->cols*0.37, digit->rows*0.68));
	int dl2Area = countInArea(digit, cv::Point(0, digit->rows*0.80), cv::Point(digit->cols*0.37, digit->rows*0.85));

	if(dl1Area && dl2Area && ulArea && !urArea)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect7(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 7
	}

	int drArea = countInArea(digit, cv::Point(digit->cols*0.90, digit->rows*0.52), cv::Point(digit->cols, digit->rows));
	int ulArea = countInArea(digit, cv::Point(0, 0), cv::Point(digit->cols*0.15, digit->rows*0.3));
	int urArea = countInArea(digit, cv::Point(digit->cols, 0), cv::Point(digit->cols*0.85, digit->rows*0.3));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.35), cv::Point(digit->cols*0.07, digit->rows*0.72));
	int lAreaDeep1 = countInArea(digit, cv::Point(0, digit->rows*0.2), cv::Point(digit->cols*0.30, digit->rows*0.27));
	int lAreaDeep2 = countInArea(digit, cv::Point(0, digit->rows*0.35), cv::Point(digit->cols*0.22, digit->rows*0.42));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.35, digit->rows*0.35), cv::Point(digit->cols*0.65, digit->rows*0.65));

	if(ulArea && urArea && !lArea && (!lAreaDeep1 || !lAreaDeep2) && cArea && !drArea)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect8(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 8
	}

	int uArea = countInArea(digit, cv::Point(digit->cols*0.43, 0), cv::Point(digit->cols*0.57, digit->rows*0.3));
	int dArea = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.70), cv::Point(digit->cols*0.57, digit->rows));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.42), cv::Point(digit->cols*0.08, digit->rows*0.60));
	int dlArea = countInArea(digit, cv::Point(0, digit->rows), cv::Point(digit->cols*0.22, digit->rows*0.52));
	int rArea = countInArea(digit, cv::Point(digit->cols, digit->rows*0.35), cv::Point(digit->cols*0.92, digit->rows*0.62));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.46, digit->rows*0.35), cv::Point(digit->cols*0.55, digit->rows*0.65));
	int urArea6 = countInArea(digit, cv::Point(digit->cols*0.63, digit->rows*0.31), cv::Point(digit->cols, digit->rows*0.32));
	int urArea5 = countInArea(digit, cv::Point(digit->cols*0.63, digit->rows*0.22), cv::Point(digit->cols, digit->rows*0.26));
	int dl1Area = countInArea(digit, cv::Point(0, digit->rows*0.65), cv::Point(digit->cols*0.23, digit->rows*0.70));
	int dl2Area = countInArea(digit, cv::Point(0, digit->rows*0.75), cv::Point(digit->cols*0.23, digit->rows*0.80));

	if(uArea && dArea && lArea && dlArea && rArea && cArea && urArea5 && urArea6 && dl1Area && dl2Area)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectionStatus detect9(const cv::Mat* digit)
{
	if(digit->rows*1.0 / digit->cols >= threshold1)
	{
		return NO_NUMBER_DETECTED;//Number to tall to be 9
	}

	int uArea = countInArea(digit, cv::Point(digit->cols*0.43, 0), cv::Point(digit->cols*0.57, digit->rows*0.3));
	int d1Area = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.70), cv::Point(digit->cols*0.50, digit->rows));
	int d2Area = countInArea(digit, cv::Point(digit->cols*0.50, digit->rows*0.70), cv::Point(digit->cols*0.57, digit->rows));
	int lArea = countInArea(digit, cv::Point(0, digit->rows*0.43), cv::Point(digit->cols*0.12, digit->rows*0.57));
	int dl1Area = countInArea(digit, cv::Point(0, digit->rows*0.65), cv::Point(digit->cols*0.23, digit->rows*0.70));
	int dl2Area = countInArea(digit, cv::Point(0, digit->rows*0.75), cv::Point(digit->cols*0.23, digit->rows*0.80));
	int rArea = countInArea(digit, cv::Point(digit->cols, digit->rows*0.35), cv::Point(digit->cols*0.93, digit->rows*0.65));
	int cArea = countInArea(digit, cv::Point(digit->cols*0.43, digit->rows*0.35), cv::Point(digit->cols*0.57, digit->rows*0.65));
	int urArea6 = countInArea(digit, cv::Point(digit->cols*0.63, digit->rows*0.29), cv::Point(digit->cols, digit->rows*0.30));
	int urArea5 = countInArea(digit, cv::Point(digit->cols*0.63, digit->rows*0.22), cv::Point(digit->cols, digit->rows*0.25));

	if(uArea && d1Area && d2Area && (!dl1Area || !dl2Area) && lArea && rArea && cArea && urArea5 && urArea6)
	{
		return NUMBER_DETECTED;
	}
	else
	{
		return NO_NUMBER_DETECTED;
	}
}

detectedDigit detectDigit(const cv::Mat* digit)
{
	detectedDigit detected;
	detected.number = NO_NUMBER_DETECTED;//-1
	detected.status = NO_NUMBER_DETECTED;
	detectionStatus tempStatus;
	switch(digitToDetect)
	{
		case firstDigitOfThreeDigitNumber:
		{
			tempStatus = detect0(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				detected.number = 0;
				detected.status = NUMBER_DETECTED;
			}
			tempStatus = detect1(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 1;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 1;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
		}
		break;
		case secondDigitOfTwoDigitNumber:
		case thirdDigitOfThreeDigitNumber:
		{
			tempStatus = detect0(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				detected.number = 0;
				detected.status = NUMBER_DETECTED;
			}
			tempStatus = detect5(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 5;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 1;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}
			}
		}
		break;
		case secondDigitOfThreeDigitNumber:
		case firstDigitOfTwoDigitNumber:
		default:
		{
			tempStatus = detect0(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				detected.number = 0;
				detected.status = NUMBER_DETECTED;
			}
			tempStatus = detect1(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 1;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 1;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect2(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 2;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 2;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect3(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 3;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 3;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect4(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 4;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 4;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect5(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 5;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 5;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect6(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 6;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 6;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect7(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 7;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 7;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect8(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 8;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 8;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
			tempStatus = detect9(digit);
			if(tempStatus == NUMBER_DETECTED)
			{
				if(detected.number == NO_NUMBER_DETECTED)
				{
					detected.number = 9;
					detected.status = NUMBER_DETECTED;
				}
				else
				{
					detected.number = detected.number*10 + 9;
					detected.status = MULTIPLE_NUMBERS_DETECTED;
				}

			}
		}
	}
	return detected;
}

detectedNumber detectNumbers(const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3)
{
	detectedNumber retNumber;

	if(!digit1->empty())
	{
		if(!digit3->empty())
		{
			digitToDetect = firstDigitOfThreeDigitNumber;//3 digit number
		}
		else
		{
			digitToDetect = firstDigitOfTwoDigitNumber;//2 digit number
		}
		retNumber.digit1 = detectDigit(digit1);
	}
	if(!digit2->empty())
	{
		if(!digit3->empty())
		{
			digitToDetect = secondDigitOfThreeDigitNumber;//3 digit number
		}
		else
		{
			digitToDetect = secondDigitOfTwoDigitNumber;//2 digit number
		}
		retNumber.digit2 = detectDigit(digit2);
	}
	if(!digit3->empty())
	{
		digitToDetect = thirdDigitOfThreeDigitNumber;
		retNumber.digit3 = detectDigit(digit3);
	}

	//the function either returns a detected number or an error code
	return retNumber;
}
