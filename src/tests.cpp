/*
 * tests.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "tests.h"
#include "img_prep.h"
#include "img_work.h"
#include "recognition.h"
#include <iostream>						//cout
#include "opencv2/highgui.hpp"			//imshow

static int numOfTests = 0;
static int correctTests = 0;

int testSelectedFunctions(cv::Mat* inp, cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	getDigits(inp, num1, num2, num3);
	return detectNumbers(num1, num2, num3);
}

void testImageReferance(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of References <==================================" << std::endl;

	//reference
	path = "images/30.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "Regular 30" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	path = "images/60.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "Regular 60" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	path = "images/80.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "Regular 80" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 80)
	{
		correctTests++;
	}

	path = "images/130.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "Regular 130" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	imshow("Regular", help1);
}

void testImages15(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 15 <===========================================" << std::endl;

	//15
	path = "images/15/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "15/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 15)
	{
		correctTests++;
	}

	path = "images/15/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "15/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 15)
	{
		correctTests++;
	}

	path = "images/15/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "15/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 15)
	{
		correctTests++;
	}

	imshow("15",help1);
}

void testImages25(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 25 <===========================================" << std::endl;

	//25
	path = "images/25/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "25/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 25)
	{
		correctTests++;
	}

	path = "images/25/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "25/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 25)
	{
		correctTests++;
	}

	imshow("25",help1);
}

void testImages30(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 30 <===========================================" << std::endl;

	//30
	path = "images/30/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "30/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	path = "images/30/2a.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "30/2a" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	path = "images/30/3a.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "30/3a" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	path = "images/30/4a.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "30/4a" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	path = "images/30/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "30/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	path = "images/30/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "30/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 30)
	{
		correctTests++;
	}

	imshow("30", help1);
}

void testImages40(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 40 <===========================================" << std::endl;

	//40
	path = "images/40/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "40/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 40)
	{
		correctTests++;
	}

	path = "images/40/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "40/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 40)
	{
		correctTests++;
	}

	path = "images/40/3.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "40/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 40)
	{
		correctTests++;
	}

	path = "images/40/4.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "40/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 40)
	{
		correctTests++;
	}

	imshow("40", help1);
}

void testImages50(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 50 <===========================================" << std::endl;

	//50
	path = "images/50/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "50/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 50)
	{
		correctTests++;
	}

	path = "images/50/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "50/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 50)
	{
		correctTests++;
	}

	path = "images/50/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "50/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 50)
	{
		correctTests++;
	}

	path = "images/50/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "50/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 50)
	{
		correctTests++;
	}

	path = "images/50/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "50/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 50)
	{
		correctTests++;
	}

	path = "images/50/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "50/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 50)
	{
		correctTests++;
	}

	imshow("50", help1);
}

void testImages60(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 60 <===========================================" << std::endl;

	//60
	path = "images/60/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "60/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	path = "images/60/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "60/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	path = "images/60/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "60/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	path = "images/60/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "60/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	path = "images/60/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "60/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	path = "images/60/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "60/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 60)
	{
		correctTests++;
	}

	imshow("60", help1);
}

void testImages70(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 70 <===========================================" << std::endl;

	//70
	path = "images/70/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "70/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 70)
	{
		correctTests++;
	}

	path = "images/70/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "70/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 70)
	{
		correctTests++;
	}

	path = "images/70/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "70/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 70)
	{
		correctTests++;
	}

	path = "images/70/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "70/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 70)
	{
		correctTests++;
	}

	path = "images/70/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "70/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 70)
	{
		correctTests++;
	}

	path = "images/70/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "70/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 70)
	{
		correctTests++;
	}

	imshow("70", help1);
}

void testImages80(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 80 <===========================================" << std::endl;

	//80
	path = "images/80/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "80/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 80)
	{
		correctTests++;
	}

	path = "images/80/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "80/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 80)
	{
		correctTests++;
	}

	path = "images/80/2a.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "80/2a" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 80)
	{
		correctTests++;
	}

	path = "images/80/2aa.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "80/2aa" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 80)
	{
		correctTests++;
	}

	imshow("80", help1);
}

void testImages90(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 90 <===========================================" << std::endl;

	//90
	path = "images/90/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "90/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "90/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "90/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/4.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "90/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/5.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "90/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "90/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/7.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "90/7" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	path = "images/90/8.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "90/8" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 90)
	{
		correctTests++;
	}

	imshow("90", help1);
}

void testImages100(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 100 <==========================================" << std::endl;

	//100
	path = "images/100/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "100/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 100)
	{
		correctTests++;
	}

	path = "images/100/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "100/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 100)
	{
		correctTests++;
	}

	path = "images/100/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "100/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 100)
	{
		correctTests++;
	}

	path = "images/100/5.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "100/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 100)
	{
		correctTests++;
	}

	path = "images/100/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "100/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 100)
	{
		correctTests++;
	}

	path = "images/100/7.jpeg";
	loadImage(&temp, path);

	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "100/7" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 100)
	{
		correctTests++;
	}

	imshow("100", help1);
}

void testImages120(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 120 <==========================================" << std::endl;

	//120
	path = "images/120/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "120/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 120)
	{
		correctTests++;
	}

	path = "images/120/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "120/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 120)
	{
		correctTests++;
	}

	path = "images/120/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "120/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 120)
	{
		correctTests++;
	}

	path = "images/120/5.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "120/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 120)
	{
		correctTests++;
	}

	path = "images/120/4.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "120/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 120)
	{
		correctTests++;
	}

	path = "images/120/7.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "120/7" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 120)
	{
		correctTests++;
	}

	imshow("120", help1);
}

void testImages130(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	cv::Mat temp;
	cv::Mat help1, help2;
	cv::String path;
	int detectedNumber;

	std::cout << "Checking Images of 130 <==========================================" << std::endl;

	//130
	path = "images/130/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	std::cout << "130/1" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	path = "images/130/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "130/2" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	path = "images/130/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	std::cout << "130/3" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	path = "images/130/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	std::cout << "130/4" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	path = "images/130/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	std::cout << "130/5" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	path = "images/130/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	std::cout << "130/6" << std::endl;
	detectedNumber = testSelectedFunctions(&temp, num1, num2, num3);
	numOfTests++;
	if(detectedNumber == 130)
	{
		correctTests++;
	}

	imshow("130", help1);
}

void testAll(cv::Mat* num1, cv::Mat* num2, cv::Mat* num3)
{
	testImageReferance(num1, num2, num3);
	testImages15(num1, num2, num3);
	testImages25(num1, num2, num3);
	testImages30(num1, num2, num3);
	testImages40(num1, num2, num3);
	testImages50(num1, num2, num3);
	testImages60(num1, num2, num3);
	testImages70(num1, num2, num3);
	testImages80(num1, num2, num3);
	testImages90(num1, num2, num3);
	testImages100(num1, num2, num3);
	testImages120(num1, num2, num3);
	testImages130(num1, num2, num3);

	std::cout << "Tests: " << correctTests << "/" << numOfTests << std::endl;
}

