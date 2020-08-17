/*
 * tests.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "tests.h"

void testScan(Mat in)
{
	horizontalScan(in, 0.35);
	horizontalScan(in, 0.42);
	horizontalScan(in, 0.50);
	horizontalScan(in, 0.58);
	horizontalScan(in, 0.65);
	verticalScan(in, 0.3);
	verticalScan(in, 0.4);
	verticalScan(in, 0.5);
	verticalScan(in, 0.6);
	verticalScan(in, 0.7);
}

void test30Lines(Mat in)
{
	int tacno = 1;
	int num;
	num = verticalScan(in, 0.3).size();
	if(num >= 5 && num <= 7) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.4).size();
	if(num >= 2 && num <= 4) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.6).size();
	if(num >= 1 && num <= 3) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.7).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;

	num = horizontalScan(in, 0.35).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.42).size();
	if(num >= 5 && num <= 7) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.58).size();
	if(num >= 5 && num <= 7) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.65).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;

	if(tacno)cout<<"Ogranicenje brzine 30"<<endl;
}
void test60Lines(Mat in)
{
	int tacno = 1;
	int num;
	num = verticalScan(in, 0.3).size();
	if(num >= 5 && num <= 7) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.4).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.6).size();
	if(num >= 1 && num <= 3) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.7).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;

	num = horizontalScan(in, 0.35).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.42).size();
	if(num >= 5 && num <= 7) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.58).size();
	if(num >= 7 && num <= 9) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.65).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;

	if(tacno)cout<<"Ogranicenje brzine 60"<<endl;
}
void test80Lines(Mat in)
{
	int tacno = 1;
	int num;
	num = verticalScan(in, 0.3).size();
	if(num >= 5 && num <= 7) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.4).size();
	if(num >= 1 && num <= 3) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.6).size();
	if(num >= 1 && num <= 3) tacno*=1;
	else tacno*=0;
	num = verticalScan(in, 0.7).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;

	num = horizontalScan(in, 0.35).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.42).size();
	if(num >= 7 && num <= 9) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.58).size();
	if(num >= 7 && num <= 9) tacno*=1;
	else tacno*=0;
	num = horizontalScan(in, 0.65).size();
	if(num >= 3 && num <= 5) tacno*=1;
	else tacno*=0;

	if(tacno)cout<<"Ogranicenje brzine 80"<<endl;
}

void testSelectedFunctions(Mat inp, Mat* num1, Mat* num2, Mat* num3)
{
//	test30Lines(inp);
//	test60Lines(inp);
//	test80Lines(inp);
	getNumbers(inp, num1, num2, num3);
	detectNumbers(*num1, *num2, *num3);
}

void testImageReferance(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp;
	Mat help1, help2;
	String path;

	cout << "Checking Images of References <==================================" << endl;

	//reference
	path = "images/30.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	temp.copyTo(help1);
	cout << "Regular 30" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/60.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "Regular 60" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/80.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	temp.copyTo(help2);
	cout << "Regular 80" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/130.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("Regular", help1);
	cout << "Regular 130" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages15(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 15 <===========================================" << endl;

	//15
	path = "images/15/1.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	temp.copyTo(help1);
	cout << "15/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/15/2.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "15/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/15/3.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "15/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	imshow("15",help1);
}

void testImages25(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 25 <===========================================" << endl;

	//25
	path = "images/25/1.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	temp.copyTo(help1);
	cout << "25/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/25/2.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "25/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	imshow("25",help1);
}

void testImages30(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 30 <===========================================" << endl;

	//30
	path = "images/30/1.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	temp.copyTo(help1);
	cout << "30/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/30/2a.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "30/2a" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/30/3a.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "30/3a" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/30/4a.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	temp.copyTo(help2);
	cout << "30/4a" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/30/5.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help2, temp, help2);
	cout << "30/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/30/6.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("30", help1);
	cout << "30/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages40(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 40 <===========================================" << endl;

	//40
	path = "images/40/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "40/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/40/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "40/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/40/3.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "40/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/40/4.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("40", help1);
	cout << "40/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages50(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 50 <===========================================" << endl;

	//50
	path = "images/50/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "50/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/50/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "50/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/50/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "50/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/50/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "50/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/50/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "50/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/50/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("50", help1);
	cout << "50/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages60(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 60 <===========================================" << endl;

	//60
	path = "images/60/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "60/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/60/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "60/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/60/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "60/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/60/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "60/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/60/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "60/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/60/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("60", help1);
	cout << "60/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages70(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 70 <===========================================" << endl;

	//70
	path = "images/70/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "70/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/70/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "70/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/70/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "70/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/70/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "70/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/70/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "70/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/70/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("70", help1);
	cout << "70/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages80(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 80 <===========================================" << endl;

	//80
	path = "images/80/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "80/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/80/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "80/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/80/2a.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "80/2a" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/80/2aa.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("80", help1);
	cout << "80/2aa" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages90(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 90 <===========================================" << endl;

	//90
	path = "images/90/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "90/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "90/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "90/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/4.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "90/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/5.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "90/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "90/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/7.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "90/7" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/90/8.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("90", help1);
	cout << "90/8" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages100(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 100 <==========================================" << endl;

	//100
	path = "images/100/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "100/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/100/2.jpeg";
	loadImage(&temp, path);
	testScan(temp);
	hconcat(help1, temp, help1);
	cout << "100/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/100/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "100/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/100/5.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "100/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/100/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "100/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/100/7.jpeg";
	loadImage(&temp, path);

	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("100", help1);
	cout << "100/7" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages120(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 120 <==========================================" << endl;

	//120
	path = "images/120/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "120/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/120/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "120/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/120/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "120/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/120/5.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "120/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/120/4.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "120/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/120/7.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("120", help1);
	cout << "120/7" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testImages130(Mat* num1, Mat* num2, Mat* num3)
{
	Mat temp, tempPure;
	Mat help1, help2;
	String path;

	cout << "Checking Images of 130 <==========================================" << endl;

	//130
	path = "images/130/1.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help1);
	cout << "130/1" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/130/2.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "130/2" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/130/3.jpeg";
	loadImage(&temp, path);
	hconcat(help1, temp, help1);
	cout << "130/3" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/130/4.jpeg";
	loadImage(&temp, path);
	temp.copyTo(help2);
	cout << "130/4" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/130/5.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	cout << "130/5" << endl;
	testSelectedFunctions(temp, num1, num2, num3);

	path = "images/130/6.jpeg";
	loadImage(&temp, path);
	hconcat(help2, temp, help2);
	vconcat(help1, help2, help1);
	imshow("130", help1);
	cout << "130/6" << endl;
	testSelectedFunctions(temp, num1, num2, num3);
}

void testAll(Mat* num1, Mat* num2, Mat* num3)
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
	testImages120(num1, num2, num3);//NOTE 120/6 ne postoji prazna linija izmedju 2 i 0
	testImages130(num1, num2, num3);

}

