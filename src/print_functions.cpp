/*
 * print.cpp
 *
 *  Created on: Sep 13, 2020
 *      Author: momcilo
 */

#include "print_functions.h"

void writeOutLoadErrors(const loadStatus* retLoadStatus, const cv::String* imageLocation)
{
	if(*retLoadStatus == STATUS_FILE_OPEN_ERROR)
	{
		std::cout << "Could not open or find the image!" << std::endl;
		std::cout << "Path: " << imageLocation << std::endl;
	}
	else if(*retLoadStatus == STATUS_WRONG_SIZE_ERROR)
	{
		std::cout << "Wrong size of the image!" << std::endl;
		std::cout << "Path: " << imageLocation << std::endl;
	}
}

void writeOutWorkErrors(const workDigitStatuses* retWorkStatuses, const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3)
{
	if(retWorkStatuses->digit1 == STATUS_UNABLE_TO_SEPARATE_NUMBERS)
	{
		std::cout << "Unable to separate numbers" << std::endl;
	}
	else
	{
		if(!digit1->empty() && ((retWorkStatuses->digit1 & STATUS_MISSING_NUMBER) == STATUS_MISSING_NUMBER))
		{
			std::cout << "Unable to detect FIRST digit" << std::endl;
		}
		if(!digit2->empty() && ((retWorkStatuses->digit2 & STATUS_MISSING_NUMBER) == STATUS_MISSING_NUMBER))
		{
			std::cout << "Unable to detect SECOND digit" << std::endl;
		}
		if(!digit3->empty() && ((retWorkStatuses->digit3 & STATUS_MISSING_NUMBER) == STATUS_MISSING_NUMBER))
		{
			std::cout << "Unable to detect THIRD digit" << std::endl;
		}

	}
}

void writeOutDetectedErrors(const detectedNumber* retDetectedNumber)
{
	if((retDetectedNumber->digit1.status & NO_NUMBER_DETECTED) == NO_NUMBER_DETECTED)
	{
		std::cout << "Unable to recognize FIRST digit" << std::endl;
	}
	else if((retDetectedNumber->digit1.status & MULTIPLE_NUMBERS_DETECTED) == MULTIPLE_NUMBERS_DETECTED)
	{
		std::cout << "Multiple numbers recognized for FIRST digit" << std::endl;
	}
	if((retDetectedNumber->digit2.status & NO_NUMBER_DETECTED) == NO_NUMBER_DETECTED)
	{
		std::cout << "Unable to recognize SECOND digit" << std::endl;
	}
	else if((retDetectedNumber->digit2.status & MULTIPLE_NUMBERS_DETECTED) == MULTIPLE_NUMBERS_DETECTED)
	{
		std::cout << "Multiple numbers recognized for SECOND digit" << std::endl;
	}
	if((retDetectedNumber->digit3.status & NO_NUMBER_DETECTED) == NO_NUMBER_DETECTED)
	{
		std::cout << "Unable to recognize THIRD digit" << std::endl;
	}
	else if((retDetectedNumber->digit3.status & MULTIPLE_NUMBERS_DETECTED) == MULTIPLE_NUMBERS_DETECTED)
	{
		std::cout << "Multiple numbers recognized for THIRD digit" << std::endl;
	}
}

void printOutDigits(const detectedNumber* digits, const bool toWrite)
{
	if(toWrite)
	{
		if(digits->digit1.status == NUMBER_DETECTED)
		{
			std::cout << "Digit1=" << digits->digit1.number << std::endl;
		}
		if(digits->digit2.status == NUMBER_DETECTED)
		{
			std::cout << "Digit2=" << digits->digit2.number << std::endl;
		}
		if(digits->digit3.status == NUMBER_DETECTED)
		{
			std::cout << "Digit3=" << digits->digit3.number << std::endl;
		}
	}
}

void printOutFullNumber(const detectedNumber* digits, const cv::Mat* digit1, const cv::Mat* digit2, const cv::Mat* digit3, const bool color)
{
	int number = 0;
	if((!digit1->empty() && digits->digit1.status != NUMBER_DETECTED)
			|| (!digit2->empty() && digits->digit2.status != NUMBER_DETECTED)
			|| (!digit3->empty() && digits->digit3.status != NUMBER_DETECTED))
	{
		return;//some digit can't be confidently recognized so no output needed since other functions will write out the error
	}
	if(!digit1->empty())
	{
		number = digits->digit1.number;
	}
	if(!digit2->empty())
	{
		number = number*10 + digits->digit2.number;
	}
	if(!digit3->empty())
	{
		number = number*10 + digits->digit3.number;
	}
	if(color)
	{
		std::cout << "Detected number = " << "\033[7;37m" << number << "\033[0m" << std::endl;
	}
	else
	{
		std::cout << "Detected number = " << number << std::endl;
	}
}

