/*
 * recognition.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "recognition.h"

float threshold1 = 2.45;

int countInArea(Mat inputDigit, Mat tmp, Point p1, Point p2)
{
	Rect mask(p1, p2);
	Mat cropped(inputDigit,mask);
	int counted = cv::countNonZero(cropped);
//	rectangle(tmp, p1, p2, Scalar(255,255,255), 1);//TODO ostatak testiranja za ispis
//	imshow("Circle Count", tmp);
	return counted;
}

void detect0(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 0

	int uArea = countInArea(digit, show, Point(digit.cols*0.40, 0), Point(digit.cols*0.60, digit.rows*0.3));
	int dArea = countInArea(digit, show, Point(digit.cols*0.40, digit.rows*0.70), Point(digit.cols*0.60, digit.rows));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.40), Point(digit.cols*0.12, digit.rows*0.60));
	int rArea = countInArea(digit, show, Point(digit.cols*0.77, digit.rows*0.65), Point(digit.cols, digit.rows*0.35));
	int cArea = countInArea(digit, show, Point(digit.cols*0.46, digit.rows*0.30), Point(digit.cols*0.54, digit.rows*0.65));

	if(uArea && dArea && lArea && rArea && !cArea) cout << "0";
}

void detect1(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1)
	{
		cout << "1";
		return;
	}

	int dlArea = countInArea(digit, show, Point(0, digit.rows*0.55), Point(digit.cols*0.41, digit.rows*0.89));
	int drArea = countInArea(digit, show, Point(digit.cols*0.58, digit.rows*0.7), Point(digit.cols, digit.rows*0.8));
	int ulArea = countInArea(digit, show, Point(0, 0), Point(digit.cols*0.15, digit.rows*0.30));
	int urArea = countInArea(digit, show, Point(digit.cols, 0), Point(digit.cols*0.96, digit.rows*0.30));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.35), Point(digit.cols*0.15, digit.rows*0.65));
	int rArea = countInArea(digit, show, Point(digit.cols, digit.rows*0.35), Point(digit.cols*0.96, digit.rows*0.65));
	int cArea = countInArea(digit, show, Point(digit.cols*0.35, digit.rows*0.35), Point(digit.cols*0.65, digit.rows*0.65));

	if(!dlArea) cout << "1";
	else if(drArea && ulArea && !urArea && !lArea && !rArea && cArea) cout << "1";
}

void detect2(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return; //Number to tall to be 2

	int uArea = countInArea(digit, show, Point(digit.cols*0.43, 0), Point(digit.cols*0.57, digit.rows*0.3));
	int dArea = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.70), Point(digit.cols*0.57, digit.rows));
	int drArea1 = countInArea(digit, show, Point(digit.cols*0.76, digit.rows*0.73), Point(digit.cols, digit.rows*0.75));
	int drArea2 = countInArea(digit, show, Point(digit.cols*0.8, digit.rows*0.80), Point(digit.cols, digit.rows));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.43), Point(digit.cols*0.07, digit.rows*0.57));
	int rArea = countInArea(digit, show, Point(digit.cols, digit.rows*0.2), Point(digit.cols*0.97, digit.rows*0.65));
	int cArea = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.35), Point(digit.cols*0.57, digit.rows*0.65));

	if(uArea && dArea && !lArea && rArea && cArea && !drArea1 && drArea2) cout << "2";
}

void detect3(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return; //Number to tall to be 3

	int uArea = countInArea(digit, show, Point(digit.cols*0.43, 0), Point(digit.cols*0.57, digit.rows*0.3));
	int urArea = countInArea(digit, show, Point(digit.cols*0.63, digit.rows*0.29), Point(digit.cols, digit.rows*0.30));
	int ulArea = countInArea(digit, show, Point(digit.cols*0.10, digit.rows*0.15), Point(digit.cols*0.30, digit.rows*0.35));
	int dArea = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.70), Point(digit.cols*0.57, digit.rows));
	int dlArea = countInArea(digit, show, Point(digit.cols*0.27, digit.rows*0.73), Point(0, digit.rows*0.79));
	int dr1Area = countInArea(digit, show, Point(digit.cols*0.76, digit.rows*0.73), Point(digit.cols, digit.rows*0.75));
	int dr2Area = countInArea(digit, show, Point(digit.cols*0.78, digit.rows*0.78), Point(digit.cols, digit.rows));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.43), Point(digit.cols*0.12, digit.rows*0.57));
	int rArea = countInArea(digit, show, Point(digit.cols, digit.rows*0.35), Point(digit.cols*0.93, digit.rows*0.65));
	int cArea = countInArea(digit, show, Point(digit.cols*0.45, digit.rows*0.35), Point(digit.cols*0.55, digit.rows*0.65));

	if(uArea && urArea && ulArea && dArea && dlArea && dr1Area && dr2Area && !lArea && rArea && cArea) cout << "3";
}

void detect4(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 4

	int ulArea = countInArea(digit, show, Point(digit.cols*0.20, 0), Point(digit.cols*0.25, digit.rows*0.25));
	int urArea = countInArea(digit, show, Point(digit.cols, 0), Point(digit.cols*0.91, digit.rows*0.60));
	int c1Area = countInArea(digit, show, Point(digit.cols*0.49, digit.rows*0.53), Point(digit.cols*0.55, digit.rows*0.60));
	int c2Area = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.62), Point(digit.cols*0.55, digit.rows*0.72));

	if(!ulArea && !urArea && (!c1Area || !c2Area)) cout << "4";
}

void detect5(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 5

	int cArea = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.35), Point(digit.cols*0.57, digit.rows*0.65));
	int urArea = countInArea(digit, show, Point(digit.cols*0.63, digit.rows*0.25), Point(digit.cols, digit.rows*0.26));
	int dlArea = countInArea(digit, show, Point(0, digit.rows*0.63), Point(digit.cols*0.37, digit.rows*0.65));

	if(cArea && !dlArea && !urArea) cout << "5";
}

void detect6(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 6

	int ulArea = countInArea(digit, show, Point(0, 0), Point(digit.cols*0.35, digit.rows*0.30));
	int urArea = countInArea(digit, show, Point(digit.cols*0.65, digit.rows*0.30), Point(digit.cols, digit.rows*0.32));
	int dl1Area = countInArea(digit, show, Point(0, digit.rows*0.65), Point(digit.cols*0.37, digit.rows*0.68));
	int dl2Area = countInArea(digit, show, Point(0, digit.rows*0.80), Point(digit.cols*0.37, digit.rows*0.85));

	if(dl1Area && dl2Area && ulArea && !urArea) cout << "6";
}

void detect7(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 7

	int drArea = countInArea(digit, show, Point(digit.cols*0.90, digit.rows*0.52), Point(digit.cols, digit.rows));
	int ulArea = countInArea(digit, show, Point(0, 0), Point(digit.cols*0.15, digit.rows*0.3));
	int urArea = countInArea(digit, show, Point(digit.cols, 0), Point(digit.cols*0.85, digit.rows*0.3));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.35), Point(digit.cols*0.07, digit.rows*0.72));
	int lAreaDeep1 = countInArea(digit, show, Point(0, digit.rows*0.2), Point(digit.cols*0.30, digit.rows*0.27));
	int lAreaDeep2 = countInArea(digit, show, Point(0, digit.rows*0.35), Point(digit.cols*0.22, digit.rows*0.42));
	int cArea = countInArea(digit, show, Point(digit.cols*0.35, digit.rows*0.35), Point(digit.cols*0.65, digit.rows*0.65));

	if(ulArea && urArea && !lArea && (!lAreaDeep1 || !lAreaDeep2) && cArea && !drArea) cout << "7";
}

void detect8(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 8

	int uArea = countInArea(digit, show, Point(digit.cols*0.43, 0), Point(digit.cols*0.57, digit.rows*0.3));
	int dArea = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.70), Point(digit.cols*0.57, digit.rows));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.42), Point(digit.cols*0.08, digit.rows*0.60));
	int dlArea = countInArea(digit, show, Point(0, digit.rows), Point(digit.cols*0.22, digit.rows*0.52));
	int rArea = countInArea(digit, show, Point(digit.cols, digit.rows*0.35), Point(digit.cols*0.92, digit.rows*0.62));
	int cArea = countInArea(digit, show, Point(digit.cols*0.46, digit.rows*0.35), Point(digit.cols*0.55, digit.rows*0.65));
	int urArea6 = countInArea(digit, show, Point(digit.cols*0.63, digit.rows*0.31), Point(digit.cols, digit.rows*0.32));
	int urArea5 = countInArea(digit, show, Point(digit.cols*0.63, digit.rows*0.22), Point(digit.cols, digit.rows*0.26));
	int dl1Area = countInArea(digit, show, Point(0, digit.rows*0.65), Point(digit.cols*0.23, digit.rows*0.70));
	int dl2Area = countInArea(digit, show, Point(0, digit.rows*0.75), Point(digit.cols*0.23, digit.rows*0.80));

	if(uArea && dArea && lArea && dlArea && rArea && cArea && urArea5 && urArea6 && dl1Area && dl2Area) cout << "8";
}

void detect9(Mat digit)
{
	Mat show;
	digit.copyTo(show);
	if(digit.rows*1.0 / digit.cols >= threshold1) return;//Number to tall to be 9"

	int uArea = countInArea(digit, show, Point(digit.cols*0.43, 0), Point(digit.cols*0.57, digit.rows*0.3));
	int d1Area = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.70), Point(digit.cols*0.50, digit.rows));
	int d2Area = countInArea(digit, show, Point(digit.cols*0.50, digit.rows*0.70), Point(digit.cols*0.57, digit.rows));
	int lArea = countInArea(digit, show, Point(0, digit.rows*0.43), Point(digit.cols*0.12, digit.rows*0.57));
	int dl1Area = countInArea(digit, show, Point(0, digit.rows*0.65), Point(digit.cols*0.23, digit.rows*0.70));
	int dl2Area = countInArea(digit, show, Point(0, digit.rows*0.75), Point(digit.cols*0.23, digit.rows*0.80));
	int rArea = countInArea(digit, show, Point(digit.cols, digit.rows*0.35), Point(digit.cols*0.93, digit.rows*0.65));
	int cArea = countInArea(digit, show, Point(digit.cols*0.43, digit.rows*0.35), Point(digit.cols*0.57, digit.rows*0.65));
	int urArea6 = countInArea(digit, show, Point(digit.cols*0.63, digit.rows*0.29), Point(digit.cols, digit.rows*0.30));
	int urArea5 = countInArea(digit, show, Point(digit.cols*0.63, digit.rows*0.22), Point(digit.cols, digit.rows*0.25));

	if(uArea && d1Area && d2Area && (!dl1Area || !dl2Area) && lArea && rArea && cArea && urArea5 && urArea6) cout << "9";
}

void numbersToDetect(Mat digit)
{
	detect0(digit);
	detect1(digit);
	detect2(digit);
	detect3(digit);
	detect4(digit);
	detect5(digit);
	detect6(digit);
	detect7(digit);
	detect8(digit);
	detect9(digit);
}

void detectNumbers(Mat digit1, Mat digit2, Mat digit3)
{
	if(!digit1.empty())
	{
		cout<<"Digit1=";
		numbersToDetect(digit1);
		cout<<endl;
	}
	if(!digit2.empty())
	{
		cout<<"Digit2=";
		numbersToDetect(digit2);
		cout<<endl;
	}
	if(!digit3.empty())
	{
		cout<<"Digit3=";
		numbersToDetect(digit3);
		cout<<endl;
	}
}

