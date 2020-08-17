/*
 * img_work.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "img_prep.h"
#include "img_work.h"

void cropOutAlmostEmpty(Mat* img)
{
	int pixelsInLine = 0;
	int emptyLineCounter;
	int lastEmptyRow1 = 0;
	int lastEmptyRow2 = img->rows;
	int lastEmptyCol1 = 0;
	int lastEmptyCol2 = img->cols;

	//UPPER HALF
	//to center
	emptyLineCounter = 0;
	for(int x = 0; x < img->rows*0.3; x++)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
			if(img->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine <= 1)emptyLineCounter++;
		if(emptyLineCounter > 1)
		{
			lastEmptyRow1 = x;//znaci da ima bar 2 uzastopne prazne linije
			emptyLineCounter--;
		}
		if(pixelsInLine >= 10) break;
	}

	//LOWER HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyRow2 = img->rows;
	for(int x = img->rows-1; x > img->rows*0.7; x--)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
			if(img->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine <= 1)emptyLineCounter++;
		if(emptyLineCounter > 1)
		{
			lastEmptyRow2 = x;
			emptyLineCounter--;
		}
		if(pixelsInLine >= 10) break;
	}

    Mat cropped(*img, Rect(0,lastEmptyRow1,img->cols,lastEmptyRow2-lastEmptyRow1));

	//LEFT HALF
	emptyLineCounter = 0;
	for(int y = cropped.cols/2; y >= 0; y--)
	{
		pixelsInLine = 0;
		for( int x = 0; x < cropped.rows -1; x++)
			if(cropped.at<uchar>(x,y))
				pixelsInLine++;
		if(pixelsInLine <= 0) emptyLineCounter++;
		if(emptyLineCounter > 1)
		{
			lastEmptyCol1 = y;
			break;
		}
	}
	if(lastEmptyCol1 > 0) lastEmptyCol1--;

	//RIGHT HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyCol2 = cropped.cols;
	bool breakFlag = false;
	for(int y = cropped.cols -1; y > cropped.cols/2; y--)
	{
		pixelsInLine = 0;
		for( int x = 0; x < cropped.rows-1; x++)
		{
			if(cropped.at<uchar>(x,y))
				pixelsInLine++;
			if(x < 3 && pixelsInLine > 0) breakFlag = true;//zbog coska kod 70/6
		}
		if(y == cropped.cols -1 && breakFlag) break;//zbog coska kod 70/6
		if(pixelsInLine <= 1)emptyLineCounter++;
		if(emptyLineCounter > 1) lastEmptyCol2 = y;
		if(pixelsInLine >= 9)
		{
			lastEmptyCol2 = y;
			break;
		}
	}
	if(lastEmptyCol2 < cropped.cols) lastEmptyCol2++;

    Mat cropped2(cropped, Rect(lastEmptyCol1,0,lastEmptyCol2-lastEmptyCol1,cropped.rows));

    cropped2.copyTo(*img);
}

void cropOutAlmostEmpty1(Mat* img)
{
	int pixelsInLine = 0;
	int emptyLineCounter;
	int lastEmptyRow1 = 0;
	int lastEmptyRow2 = img->rows;
	int lastEmptyCol1 = 0;
	int lastEmptyCol2 = img->cols;

	//UPPER HALF
	//to center
	emptyLineCounter = 0;
	for(int x = 0; x < img->rows*0.3; x++)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
			if(img->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine <= 1)emptyLineCounter++;
		if(emptyLineCounter > 1)
		{
			lastEmptyRow1 = x;//znaci da ima bar 2 uzastopne prazne linije
			emptyLineCounter--;
		}
		if(pixelsInLine >= 10) break;
	}
	if(lastEmptyRow1 > 0) lastEmptyRow1--; //da bi mogao da se vidi i poslednji red sa linijom (da je ne isece)

	//LOWER HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyRow2 = img->rows;
	for(int x = img->rows -1; x > img->rows*0.7; x--)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
			if(img->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine == 0)lastEmptyRow2 = x;
		else break;
	}
	if(lastEmptyRow2 < img->rows) lastEmptyRow2++;

	//check for empty space before cropping
	int levo = 0;
	for(int y = img->cols/2; y > 0; y--)
	{
		pixelsInLine = 0;
		for( int x = 1; x < img->rows; x++)
		{
			if(img->at<uchar>(x,y))
				pixelsInLine++;
		}
		if(pixelsInLine != 0)
			break;
		else
			levo = y;
	}
	if(levo > 1) levo--;//da se vidi linija

    Mat cropped(*img, Rect(levo,lastEmptyRow1,img->cols-levo,lastEmptyRow2-lastEmptyRow1));

    //SIDES
	int leftLine = 0;
	int rightLine = cropped.cols-1;
	vector<int> linije;
	vector<int> duzine;
	int max1 = 0;
	int max2 = 0;
	int line1 = 1;
	int line2 = cropped.cols-1;

	//naci sve linije preko odredjene duzine
	for(int y = 0; y < cropped.cols; y++)
	{
		pixelsInLine = 1;
		for( int x = 0; x < cropped.rows; x++)
		{
			if(x > 0 && cropped.at<uchar>(x,y) && cropped.at<uchar>(x-1,y))
				pixelsInLine++;
			else
			{
				if(pixelsInLine > cropped.rows/6)
				{
					linije.push_back(y);
					duzine.push_back(pixelsInLine);
				}
				pixelsInLine = 1;
			}
		}
	}

	//izbaciti susedne linije
	for(int i = 1; i < linije.size(); i++)
	{
		if(linije[i] == linije[i-1]
			|| linije[i] == linije[i-1]+1)
		{
			int toRemove;
			if(duzine[i] > duzine[i-1]) toRemove = i-1;
			else toRemove = i;
			linije.erase(linije.begin()+toRemove);
			duzine.erase(duzine.begin()+toRemove);
			i--;
		}
	}

	//nalazenje 2 najvece linije
	for(int i = 0; i < linije.size(); i++)
	{
		if(duzine[i] > max1)
		{
			max2 = max1;
			line2 = line1;
			max1 = duzine[i];
			line1 = linije[i];
		}
		else if(duzine[i] > max2)
		{
			max2 = duzine[i];
			line2 = linije[i];
		}
	}
	//line1/max1 da bude leva linija
	if(line2 < line1)
	{
		std::swap(line1, line2);
		std::swap(max1, max2);
	}

	//nalazenje susednih linija
	//levo
	int initLimit = line1;
	for(int y = initLimit-1; y > initLimit-20; y--)
	{
		if(y < 0) break;
		pixelsInLine = 1;
		for( int x = 1; x < cropped.rows; x++)
		{
			if(cropped.at<uchar>(x,y))
				pixelsInLine++;
			else
			{
				if(pixelsInLine > 5)
				{
					line1 = y;
					break;
				}
				pixelsInLine = 1;
			}
		}
	}
	//desno
	initLimit = line2;
	for(int y = initLimit+1; y < initLimit+20; y++)
	{
		if(y > cropped.cols) break;
		pixelsInLine = 0;
		for( int x = 1; x < cropped.rows; x++)
			if(cropped.at<uchar>(x,y))
				pixelsInLine++;
		if(pixelsInLine == 0)
		{
			line2 = y;
			break;
		}
	}

    Mat cropped2(cropped, Rect(line1,0,line2-line1,cropped.rows));

    cropped2.copyTo(*img);
}

void cropOutAlmostEmpty0(Mat* img)
{
	int pixelsInLine = 0;
	int emptyLineCounter = 0;
	int lastEmptyRow1 = 0;
	int lastEmptyRow2 = img->rows;
	int lastEmptyCol1 = 0;
	int lastEmptyCol2 = img->cols;

	//UPPER HALF
	//to center
	emptyLineCounter = 0;
	for(int x = 0; x < img->rows*0.3; x++)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
			if(img->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine <= 1)emptyLineCounter++;
		if(emptyLineCounter > 1)
		{
			lastEmptyRow1 = x;//znaci da ima bar 2 uzastopne prazne linije
			emptyLineCounter--;
		}
		if(pixelsInLine >= 10) break;
	}
	if(lastEmptyRow1 > 0) lastEmptyRow1--; //da bi mogao da se vidi i poslednji red sa linijom (da je ne isece)

	//LOWER HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyRow2 = img->rows;
	for(int x = img->rows-1; x > img->rows*0.7; x--)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
			if(img->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine <= 1)emptyLineCounter++;
		if(emptyLineCounter > 1)
		{
			lastEmptyRow2 = x;
			emptyLineCounter--;
		}
		if(pixelsInLine >= 6)
		{
			lastEmptyRow2 = x;
			break;
		}
	}
	if(lastEmptyRow2 < img->rows) lastEmptyRow2++;

    Mat cropped(*img, Rect(0,lastEmptyRow1,img->cols,lastEmptyRow2-lastEmptyRow1));

	//SIDES
    int leftLine = 0;
    int rightLine = cropped.cols-1;
    vector<int> linije;
    vector<int> duzine;
	int max1 = 0;
	int max2 = 0;
	int line1 = 1;
	int line2 = cropped.cols-1;
    for(int y = 0; y < cropped.cols; y++)
	{
		pixelsInLine = 1;
		for( int x = 1; x < cropped.rows; x++)
		{
			if(cropped.at<uchar>(x,y) && cropped.at<uchar>(x-1,y))
				pixelsInLine++;
			else
			{
				if(pixelsInLine > 9)
				{
					linije.push_back(y);
					duzine.push_back(pixelsInLine);
				}
				pixelsInLine = 1;
			}
		}
	}

    //izbaciti susedne linije
	for(int i = 1; i < linije.size(); i++)
	{
		if(linije[i] == linije[i-1]
			|| linije[i] == linije[i-1]+1)
		{
			int toRemove;
			if(duzine[i] > duzine[i-1]) toRemove = i-1;
			else toRemove = i;
			linije.erase(linije.begin()+toRemove);
			duzine.erase(duzine.begin()+toRemove);
			i--;
		}
	}

	int maxLength = 0;
	for(int i = 0; i < linije.size()-1; i++)
		if(duzine[i] > maxLength) maxLength = duzine[i];
	int counter = 0;
	int comp = maxLength>35?15:10;
	for(int i = 0; i < linije.size(); i++)
		{
		if(duzine[i] >= comp && counter < 4)
		{
			if(counter == 0)
			{
				max1 = duzine[i];
				line1 = linije[i];
			}
			else if(counter == 3)
			{
				max2 = duzine[i];
				line2 = linije[i] +1;//da se vidi poslednja linija
				break;
			}
			counter++;
		}
	}

    Mat cropped2(cropped, Rect(line1,0,line2-line1,cropped.rows));

    cropped2.copyTo(*img);
}


Point innerCircleH(Mat in, float ratio)
{
	int margin = in.cols*0.05;
	int midHeight = in.rows*ratio;
	int start = -1;
	int end;
	int point;
	for(int i = margin; i < in.cols-margin; i++)
		if(in.at<uchar>(midHeight,i) > 0)
		{
			point = i;
			if(start == -1) start = point;
		}
//	end = point;
	if(start == -1){
		start = 0;
		end = in.rows;
	} else {
		if(start > in.rows/2) start = 0;
		end = point;
	}
	return Point(start, end);
}


Point innerCircleV(Mat in, float ratio)
{
	int margin = in.rows*0.05;
	int midWidth = in.cols*ratio;
	int start = -1;
	int end;
	int point;
	for(int i = margin; i < in.rows-margin; i++)
		if(in.at<uchar>(i, midWidth) > 0)
		{
			point = i;
			if(start == -1) start = point;
		}
	if(start == -1){
		start = 0;
		end = in.rows;
	} else {
		if(start > in.rows/2) start = 0;
		end = point;
	}

	return Point(start, end);
}


vector<int> horizontalScan(Mat in, float ratio)
{
	vector<int> points;
	Point margins = innerCircleH(in, ratio);
	int midHeight = in.rows*ratio;
	bool linija = false;
	if(margins.x > in.cols*0.1) points.push_back(margins.x);
	for(int i = margins.x +1; i < margins.y; i++)
	{
		if(in.at<uchar>(midHeight,i) == 0) linija = false;
		if(in.at<uchar>(midHeight,i) > 0 && i+1 != margins.y)
		{
			if(i > margins.x +4
					&& in.at<uchar>(midHeight, i) > 0
					&& in.at<uchar>(midHeight, i-1) > 0
					&& in.at<uchar>(midHeight, i-2) > 0) linija = true;
			if(in.at<uchar>(midHeight, i-1) == 0
					|| (in.at<uchar>(midHeight, i+1) == 0 && linija))
				points.push_back(i);
		}
	}
	if(margins.y < in.cols*0.9) points.push_back(margins.y);

	return points;
}


vector<int> verticalScan(Mat in, float ratio)
{
	vector<int> points;
	Point margins = innerCircleV(in, ratio);
	margins.x = 0;
	margins.y = in.rows;
	int midWidth = in.cols*ratio;
	bool linija = false;
	for(int i = margins.x +1; i < margins.y; i++)
	{
		if(in.at<uchar>(i, midWidth) == 0) linija = false;
		else if(in.at<uchar>(i, midWidth) > 0 && i+1 != margins.y)
		{
			if(i > margins.x +4
					&& in.at<uchar>(i, midWidth) > 0
					&& in.at<uchar>(i-1, midWidth) > 0
					&& in.at<uchar>(i-2, midWidth) > 0) linija = true;
			if(in.at<uchar>(i-1, midWidth) == 0
					|| (in.at<uchar>(i+1, midWidth) == 0 && linija))
				points.push_back(i);
		}
	}

	return points;
}


int getCentralLine(Mat in, int start, int end)
{
	int found = -1;
	if(start > 50 && end > 50) found = 301; //zbog uslova kad se gleda izmedju 2 i 3 cifre
	for(int i = start; i <= end; i++)//mora int umesto float jer zbog konverzije umesto 150 vidi 149
	{
		vector<int> scanLines = verticalScan(in, i*1.0/100);
		if(verticalScan(in, i*1.0/100).size() == 0)
			if((in.cols*i/100 >= in.cols/2 && in.cols*i/100 < found)
					|| (in.cols*i/100 <= in.cols/2 && in.cols*i/100 > found))
				found = in.cols*i/100;
	}
	if(found == 301) found = -1;

	return found;
}


int getNumberOfDigits(Mat in)
{
	int pixelsInLine = 0;

	int centralLine = -1;
	for(int i = 44; i < 53; i++)
	{
		pixelsInLine = 0;
		int y = in.cols*i*1.0/100;
		for(int x = 0; x < in.rows; x++)
			if(in.at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine == 0)
		{
			centralLine = y;
			break;
		}
		if(centralLine != -1) break;
	}

	if(centralLine == -1) return 3; //Imaju 3 cifre
	else return centralLine; // Imaju 2 cifre
}


Point getCentralLines(Mat in)
{
	Point retVal;
	//LEFT LINE 1/2
	retVal.x = getCentralLine(in, 29, 39);

	//RIGHT LINE 2/3
	retVal.y = getCentralLine(in, 56, 63);

	return retVal;
}


void isolateNumbersV(Mat* srcImage)
{
	int margin = 0;
	int pixelsInLine;
	int top = 0;
	int bottom = srcImage->rows;
	for(int x = srcImage->rows*0.5; x > srcImage->rows*0.2; x--)
	{
		pixelsInLine = 0;
		if(!(x%2)) margin++;
		for( int y = srcImage->cols*0.2+margin; y < srcImage->cols*0.8-margin; y++)
			if(srcImage->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine == 0)
		{
			top = x;
			break;
		}
	}
	margin = 0;
	for(int x = srcImage->rows*0.5; x < srcImage->rows*0.8; x++)
	{
		pixelsInLine = 0;
		if(!(x%2)) margin++;
		for( int y = srcImage->cols*0.2+margin; y < srcImage->cols*0.8-margin; y++)
			if(srcImage->at<uchar>(x,y) > 0)
				pixelsInLine++;
		if(pixelsInLine == 0)
		{
			bottom = x;
			break;
		}
	}
	Mat cropped(*srcImage,Rect(0, top, srcImage->cols, bottom-top));
	cropped.copyTo(*srcImage);
}


void getNumbers(Mat srcImage, Mat* digit1, Mat* digit2, Mat* digit3)
{
	digit1->release();
	digit2->release();
	digit3->release();
	int left = srcImage.cols;
	int right = 0;
	int levaStrana = srcImage.cols;
	int desnaStrana = 0;

	isolateNumbersV(&srcImage);
	int numberOfNumbers = getNumberOfDigits(srcImage);
	if(numberOfNumbers != 3)//2 cifre
	{
		int sredina = numberOfNumbers;
		vector<int> linija;
		for(float mov = 0.1; mov <= 0.9; mov+=0.01)
		{
			linija = horizontalScan(srcImage, mov);
			for(int i = 0; i < linija.size(); i++)
			{
				if(linija[i] < levaStrana && linija[i] > srcImage.cols*0.15) levaStrana = linija[i];
				if(linija[i] > desnaStrana && linija[i] < srcImage.cols*0.87) desnaStrana = linija[i];
			}
		}

		//LEFT NUMBER
		right = sredina;
		left = levaStrana;
	    Mat croppedLeft(srcImage, Rect(left,0,right-left,srcImage.rows));
	    cropOutAlmostEmpty(&croppedLeft);
	    croppedLeft.copyTo(*digit1);

		//RIGHT NUMBER
		right = desnaStrana;
		left = sredina;
	    Mat croppedRight(srcImage, Rect(left,0,right-left,srcImage.rows));
	    cropOutAlmostEmpty(&croppedRight);
	    croppedRight.copyTo(*digit2);
	}
	else//3 cifre
	{
		Point centralLines = getCentralLines(srcImage);
		int sredinaL = centralLines.x;
		int sredinaD = centralLines.y;
		if(sredinaL == -1 || sredinaD == -1)
		{
			cout << "Ne mogu se razdvojiti cifre" << endl;
			exit(2);
		}

		vector<int> linija = horizontalScan(srcImage, 0.35);
		for(float mov = 0.1; mov <= 0.9; mov+=0.01)
		{
			linija = horizontalScan(srcImage, mov);
			for(int i = 0; i < linija.size(); i++)
			{
				if(linija[i] < levaStrana && linija[i] > srcImage.cols*0.15) levaStrana = linija[i];
				if(linija[i] > desnaStrana && linija[i] < srcImage.cols*0.90) desnaStrana = linija[i];
			}
		}

		//LEFT NUMBER
		right = sredinaL;
		left = levaStrana -1;//da bi se videla i sama linija
	    Mat croppedLeft(srcImage, Rect(left,0,right-left,srcImage.rows));
	    cropOutAlmostEmpty1(&croppedLeft);
	    croppedLeft.copyTo(*digit1);

		//CENTER NUMBER
		right = sredinaD;
		left = sredinaL;
	    Mat croppedCenter(srcImage, Rect(left,0,right-left,srcImage.rows));
	    cropOutAlmostEmpty(&croppedCenter);
	    croppedCenter.copyTo(*digit2);

		//RIGHT NUMBER
		right = desnaStrana +1;//da bi se videla i sama linija
		left = sredinaD;
	    Mat croppedRight(srcImage, Rect(left,0,right-left,srcImage.rows));
	    cropOutAlmostEmpty0(&croppedRight);
	    croppedRight.copyTo(*digit3);
	}
}
