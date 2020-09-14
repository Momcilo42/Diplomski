/*
 * img_work.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "img_prep.h"
#include "img_work.h"
#include <algorithm>					//for swap

static const int errorDetected = -1;

void cropOutAlmostEmpty(cv::Mat* img)
{
	int pixelsInLine = 0;
	int emptyLineCounter = 0;;
	int lastEmptyRow1 = 0;
	int lastEmptyRow2 = img->rows;
	int lastEmptyCol1 = 0;
	int lastEmptyCol2 = img->cols;

	static const int allowedVerticalPixels = 10;

	//UPPER HALF
	//to center
	emptyLineCounter = 0;
	for(int x = 0; x < img->rows*0.3; x++)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
		{
			if(img->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine <= 1)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyRow1 = x;//has at least 2 consequtive empty lines
			emptyLineCounter--;
		}
		if(pixelsInLine >= allowedVerticalPixels)
		{
			break;
		}
	}

	//LOWER HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyRow2 = img->rows;
	for(int x = img->rows-1; x > img->rows*0.7; x--)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
		{
			if(img->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine <= 1)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyRow2 = x;
			emptyLineCounter--;
		}
		if(pixelsInLine >= allowedVerticalPixels)
		{
			break;
		}
	}

	//crops out the upper and lower parts to help with sideways detection
	cv::Mat cropped(*img, cv::Rect(0,lastEmptyRow1,img->cols,lastEmptyRow2-lastEmptyRow1));

	//LEFT HALF
	emptyLineCounter = 0;
	for(int y = cropped.cols/2; y >= 0; y--)
	{
		pixelsInLine = 0;
		for( int x = 0; x < cropped.rows -1; x++)
		{
			if(cropped.at<uchar>(x,y))
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine <= 0)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyCol1 = y;
			break;
		}
	}
	if(lastEmptyCol1 > 0)
	{
		lastEmptyCol1--;
	}

	//RIGHT HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyCol2 = cropped.cols;
	bool breakFlag = false;
	static const int allowedSidePixels = 9;

	//remove empty lines
	for(int y = cropped.cols -1; y > cropped.cols/2; y--)
	{
		pixelsInLine = 0;
		for( int x = 0; x < cropped.rows-1; x++)
		{
			if(cropped.at<uchar>(x,y))
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine == 0)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyCol2 = y;
		}
		if(pixelsInLine > 0)
		{
			lastEmptyCol2 = y;
			break;
		}
	}

	//compensate for lines on the right side if necessary
	for(int y = lastEmptyCol2; y > cropped.cols/2; y--)
	{
		pixelsInLine = 0;
		for( int x = 0; x < cropped.rows-1; x++)
		{
			if(cropped.at<uchar>(x,y))
			{
				pixelsInLine++;
			}
			if(pixelsInLine > 0 && x < 3)
			{
				breakFlag = true;//because of the sharp corner in picture 70/6
			}
		}
		if(y == lastEmptyCol2 && breakFlag)
		{
			break;//because of the sharp corner in picture 70/6
		}
		if(pixelsInLine <= 1)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyCol2 = y;
		}
		if(pixelsInLine >= allowedSidePixels)
		{
			lastEmptyCol2 = y;
			break;
		}
	}
	if(lastEmptyCol2 < cropped.cols)
	{
		lastEmptyCol2++;
	}

	//final crop out of the digit
	cv::Mat cropped2(cropped, cv::Rect(lastEmptyCol1,0,lastEmptyCol2-lastEmptyCol1,cropped.rows));

    *img = std::move(cropped2);
}

void cropOutAlmostEmptyLeftmost1(cv::Mat* img)
{
	int pixelsInLine = 0;
	int emptyLineCounter = 0;
	int lastEmptyRow1 = 0;
	int lastEmptyRow2 = img->rows;

	static const int allowedVerticalPixels = 10;

	//UPPER HALF
	//to center
	for(int x = 0; x < img->rows*0.3; x++)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
		{
			if(img->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine <= 1)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyRow1 = x;//has at least 2 consequtive empty lines
			emptyLineCounter--;
		}
		if(pixelsInLine >= allowedVerticalPixels)
		{
			break;
		}
	}
	if(lastEmptyRow1 > 0)
	{
		lastEmptyRow1--; //to show the last line
	}

	//LOWER HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyRow2 = img->rows;
	for(int x = img->rows -1; x > img->rows*0.7; x--)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
		{
			if(img->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine == 0)
		{
			lastEmptyRow2 = x;
		}
		else
		{
			break;
		}
	}
	if(lastEmptyRow2 < img->rows)
	{
		lastEmptyRow2++;
	}

	//check for empty space before cropping
	int left = 0;
	for(int y = img->cols/2; y > 0; y--)
	{
		pixelsInLine = 0;
		for( int x = 1; x < img->rows; x++)
		{
			if(img->at<uchar>(x,y))
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine != 0)
		{
			break;
		}
		else
		{
			left = y;
		}
	}
	if(left > 1)
	{
		left--;//to show the last line
	}

	//crops out the upper and lower parts to help with sideways detection
	cv::Mat cropped(*img, cv::Rect(left,lastEmptyRow1,img->cols-left,lastEmptyRow2-lastEmptyRow1));

    //SIDES
	std::vector<int> lines;
	std::vector<int> lengths;
	int max1 = 0;
	int max2 = 0;
	int line1 = 1;
	int line2 = cropped.cols-1;
	static const int certainLength = cropped.rows/6;

	//find all lines over a certain length
	for(int y = 0; y < cropped.cols; y++)
	{
		pixelsInLine = 1;
		for( int x = 0; x < cropped.rows; x++)
		{
			if(x > 0 && cropped.at<uchar>(x,y) && cropped.at<uchar>(x-1,y))
			{
				pixelsInLine++;
			}
			else
			{
				if(pixelsInLine > certainLength)
				{
					lines.push_back(y);
					lengths.push_back(pixelsInLine);
				}
				pixelsInLine = 1;
			}
		}
	}

	//remove adjacent lines
	for(int i = 1; i < (int)lines.size(); i++)
	{
		if(lines[i] == lines[i-1]
			|| lines[i] == lines[i-1]+1)
		{
			int toRemove;
			if(lengths[i] > lengths[i-1])
			{
				toRemove = i-1;
			}
			else
			{
				toRemove = i;
			}
			lines.erase(lines.begin()+toRemove);
			lengths.erase(lengths.begin()+toRemove);
			i--;
		}
	}

	//find 2 longest lines
	for(int i = 0; i < (int)lines.size(); i++)
	{
		if(lengths[i] > max1)
		{
			max2 = max1;
			line2 = line1;
			max1 = lengths[i];
			line1 = lines[i];
		}
		else if(lengths[i] > max2)
		{
			max2 = lengths[i];
			line2 = lines[i];
		}
	}
	//line1/max1 leftmost line
	if(line2 < line1)
	{
		std::swap(line1, line2);	// @suppress("Invalid arguments")
		std::swap(max1, max2);		// @suppress("Invalid arguments")
	}

	//find nearest lines
	//left
	int initLimit = line1;
	static const int newLineLengthLimit = 5;
	for(int y = initLimit-1; y > initLimit-20; y--)
	{
		if(y < 0)
		{
			break;
		}
		pixelsInLine = 1;
		for( int x = 1; x < cropped.rows; x++)
		{
			if(cropped.at<uchar>(x,y))
			{
				pixelsInLine++;
			}
			else
			{
				if(pixelsInLine > newLineLengthLimit)
				{
					line1 = y;
					break;
				}
				pixelsInLine = 1;
			}
		}
	}
	//right
	initLimit = line2;
	for(int y = initLimit+1; y < initLimit+20; y++)
	{
		if(y > cropped.cols)
		{
			break;
		}
		pixelsInLine = 0;
		for( int x = 1; x < cropped.rows; x++)
		{
			if(cropped.at<uchar>(x,y))
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine == 0)
		{
			line2 = y;
			break;
		}
	}

	//final crop out of the digit
	cv::Mat cropped2(cropped, cv::Rect(line1,0,line2-line1,cropped.rows));

    *img = std::move(cropped2);
}

void cropOutAlmostEmptyRightmost0(cv::Mat* img)
{
	int pixelsInLine = 0;
	int emptyLineCounter = 0;
	int lastEmptyRow1 = 0;
	int lastEmptyRow2 = img->rows;

	static const int allowedVerticalPixelsUp = 10;
	static const int allowedVerticalPixelsDown = 6;

	//UPPER HALF
	//to center
	emptyLineCounter = 0;
	for(int x = 0; x < img->rows*0.3; x++)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
		{
			if(img->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine <= 1)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyRow1 = x;//has at least 2 consequtive empty lines
			emptyLineCounter--;
		}
		if(pixelsInLine >= allowedVerticalPixelsUp)
		{
			break;
		}
	}
	if(lastEmptyRow1 > 0)
	{
		lastEmptyRow1--; //to show the last line
	}

	//LOWER HALF
	//to center
	emptyLineCounter = 0;
	lastEmptyRow2 = img->rows;
	for(int x = img->rows-1; x > img->rows*0.7; x--)
	{
		pixelsInLine = 0;
		for( int y = 0; y < img->cols; y++)
		{
			if(img->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine <= 1)
		{
			emptyLineCounter++;
		}
		if(emptyLineCounter > 1)
		{
			lastEmptyRow2 = x;
			emptyLineCounter--;
		}
		if(pixelsInLine >= allowedVerticalPixelsDown)
		{
			lastEmptyRow2 = x;
			break;
		}
	}
	if(lastEmptyRow2 < img->rows)
	{
		lastEmptyRow2++;
	}

	//crops out the upper and lower parts to help with sideways detection
	cv::Mat cropped(*img, cv::Rect(0,lastEmptyRow1,img->cols,lastEmptyRow2-lastEmptyRow1));

	//SIDES
    std::vector<int> linije;
    std::vector<int> duzine;
	int line1 = 1;
	int line2 = cropped.cols-1;

	static const int certainLength = 9;

	//find all lines over a certain length
    for(int y = 0; y < cropped.cols; y++)
	{
		pixelsInLine = 1;
		for( int x = 1; x < cropped.rows; x++)
		{
			if(cropped.at<uchar>(x,y) && cropped.at<uchar>(x-1,y))
			{
				pixelsInLine++;
			}
			else
			{
				if(pixelsInLine > certainLength)
				{
					linije.push_back(y);
					duzine.push_back(pixelsInLine);
				}
				pixelsInLine = 1;
			}
		}
	}

    //remove adjacent lines
	for(int i = 1; i < (int)linije.size(); i++)
	{
		if(linije[i] == linije[i-1]
			|| linije[i] == linije[i-1]+1)
		{
			int toRemove;
			if(duzine[i] > duzine[i-1])
			{
				toRemove = i-1;
			}
			else
			{
				toRemove = i;
			}
			linije.erase(linije.begin()+toRemove);
			duzine.erase(duzine.begin()+toRemove);
			i--;
		}
	}

	//find longest line
	int maxLength = 0;
	for(int i = 0; i < (int)linije.size()-1; i++)
	{
		if(duzine[i] > maxLength)
		{
			maxLength = duzine[i];
		}
	}

	//determine comparative line length based on longest line
	static const int comparativeLength = 35;
	static const int higherThreshold = 15;
	static const int lowerThreshold = 10;
	int counter = 0;
	int comp = maxLength>comparativeLength?higherThreshold:lowerThreshold;

	//find 4 longest lines to get the first and last as edges
	for(int i = 0; i < (int)linije.size(); i++)
	{
		if(duzine[i] >= comp && counter < 4)
		{
			if(counter == 0)
			{
				line1 = linije[i];
			}
			else if(counter == 3)
			{
				line2 = linije[i] +1;//to show the last line
				break;
			}
			counter++;
		}
	}

	//final crop out of the digit
	cv::Mat cropped2(cropped, cv::Rect(line1,0,line2-line1,cropped.rows));

    *img = std::move(cropped2);
}

std::pair<int,int> innerCircleLeftRightEdgeDetection(const cv::Mat* in, float ratio)
{
	//5% tolerance for possible debris on the edges
	int margin = in->cols*0.05;
	int midHeight = in->rows*ratio;
	int start = errorDetected;
	int end;
	int point;
	for(int i = margin; i < in->cols-margin; i++)
	{
		if(in->at<uchar>(midHeight,i) > 0)
		{
			point = i;
			if(start == errorDetected) start = point;
		}
	}
	if(start == errorDetected)
	{
		start = 0;
		end = in->cols;
	}
	else
	{
		if(start > in->cols/2)
		{
			start = 0;
		}
		end = point;
	}
	return std::pair<int,int>(start, end);
}

std::vector<int> horizontalScan(const cv::Mat* in, float ratio)
{
	std::vector<int> points;
	std::pair<int,int> margins = innerCircleLeftRightEdgeDetection(in, ratio);
	int midHeight = in->rows*ratio;
	bool lineExists = false;
	//if margin is further than 10% away form the edge include it
	if(margins.first > in->cols*0.1)
	{
		points.push_back(margins.first);
	}
	for(int i = margins.first +1; i < margins.second; i++)
	{
		if(in->at<uchar>(midHeight,i) == 0)
		{
			lineExists = false;
		}
		if(in->at<uchar>(midHeight,i) > 0 && i+1 != margins.second)
		{
			if(i > margins.first +4
					&& in->at<uchar>(midHeight, i) > 0
					&& in->at<uchar>(midHeight, i-1) > 0
					&& in->at<uchar>(midHeight, i-2) > 0)
			{
				lineExists = true;
			}
			if(in->at<uchar>(midHeight, i-1) == 0
					|| (in->at<uchar>(midHeight, i+1) == 0 && lineExists))
			{
				points.push_back(i);
			}
		}
	}
	//if margin is further than 10% away form the edge include it
	if(margins.second < in->cols*0.9)
	{
		points.push_back(margins.second);
	}

	return points;
}

std::vector<int> verticalScan(const cv::Mat* in, float ratio)
{
	std::vector<int> points;
	std::pair<int,int> margins;
	margins.first = 0;
	margins.second = in->rows;
	int midWidth = in->cols*ratio;
	bool lineExists = false;
	for(int i = margins.first +1; i < margins.second; i++)
	{
		if(in->at<uchar>(i, midWidth) == 0)
		{
			lineExists = false;
		}
		else
		{
			if(in->at<uchar>(i, midWidth) > 0 && i+1 != margins.second)
			{
				//line is defined as 3 consecutive pixels
				if(i > margins.first +4
						&& in->at<uchar>(i, midWidth) > 0
						&& in->at<uchar>(i-1, midWidth) > 0
						&& in->at<uchar>(i-2, midWidth) > 0)
				{
					lineExists = true;
				}
				if(in->at<uchar>(i-1, midWidth) == 0
						|| (in->at<uchar>(i+1, midWidth) == 0 && lineExists))
				{
					points.push_back(i);
				}
			}
		}
	}

	return points;
}

int findEmptyLineBetweenThresholds(const cv::Mat* in, int thresholdLow, int thresholdHigh)
{
	static const int halfWidth = 50;//50%
	int found = errorDetected;
	if(thresholdLow > halfWidth && thresholdHigh > halfWidth)
	{
		found = 301; //for the case when checking between the 2 and 3 digit
	}
	for(int i = thresholdLow; i <= thresholdHigh; i++)//it has to be int instead of float because when converting instead of seeing 150 sees 149
	{
		std::vector<int> scanLines = verticalScan(in, i/100.0);
		if(scanLines.size() == 0)
		{
			if((in->cols*i/100 >= in->cols/2 && in->cols*i/100 < found)
					|| (in->cols*i/100 <= in->cols/2 && in->cols*i/100 > found))
			{
				found = in->cols*i/100;
			}
		}
	}
	if(found == 301)
	{
		found = errorDetected;
	}

	return found;
}

std::pair<int,int> getLinesBetweenDigits(const cv::Mat* in)
{
	std::pair<int,int> retVal;

	static const int lowerWidthThresholdCenter = 44;
	static const int higherWidthThresholdCenter = 53;

	//CENTRAL LINE
	int twoDigitDelimiter = findEmptyLineBetweenThresholds(in, lowerWidthThresholdCenter, higherWidthThresholdCenter);

	if(twoDigitDelimiter != errorDetected)
	{
		retVal.first = twoDigitDelimiter;

		retVal.second = errorDetected;
	}
	else
	{
		static const int lowerWidthThresholdLeft = 29;
		static const int higherWidthThresholdLeft = 39;

		static const int lowerWidthThresholdRight = 56;
		static const int higherWidthThresholdRight = 63;

		//LEFT LINE 1/2
		retVal.first = findEmptyLineBetweenThresholds(in, lowerWidthThresholdLeft, higherWidthThresholdLeft);

		if(retVal.first == errorDetected)//if it can't find the line between the first two digits it doesn't matter if the line between the second two exists
		{
			retVal.second = errorDetected;
		}
		else
		{
			//RIGHT LINE 2/3
			retVal.second = findEmptyLineBetweenThresholds(in, lowerWidthThresholdRight, higherWidthThresholdRight);

			if(retVal.second == errorDetected)//if it can't find the line between the second two digits, resets the first value to signal the error
			{
				retVal.first = errorDetected;
			}

		}
	}

	return retVal;
}

void cutOffImageAboveAndBelowTheNumbers(cv::Mat* srcImage)
{
	int margin = 0;
	int pixelsInLine;
	int top = 0;
	int bottom = srcImage->rows;

	//search upper trapezoid
	for(int x = srcImage->rows*0.5; x > srcImage->rows*0.2; x--)
	{
		pixelsInLine = 0;
		if(!(x%2))//increase margin every other number
		{
			margin++;
		}
		for( int y = srcImage->cols*0.2+margin; y < srcImage->cols*0.8-margin; y++)
		{
			if(srcImage->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine == 0)
		{
			top = x;
			break;
		}
	}

	//search lower trapezoid
	margin = 0;
	for(int x = srcImage->rows*0.5; x < srcImage->rows*0.8; x++)
	{
		pixelsInLine = 0;
		if(!(x%2))//increase margin every other number
		{
			margin++;
		}
		for( int y = srcImage->cols*0.2+margin; y < srcImage->cols*0.8-margin; y++)
		{
			if(srcImage->at<uchar>(x,y) > 0)
			{
				pixelsInLine++;
			}
		}
		if(pixelsInLine == 0)
		{
			bottom = x;
			break;
		}
	}
	cv::Mat cropped(*srcImage,cv::Rect(0, top, srcImage->cols, bottom-top));

	*srcImage = std::move(cropped);
}

workDigitStatuses getDigits(cv::Mat* srcImage, cv::Mat* digit1, cv::Mat* digit2, cv::Mat* digit3)
{
	digit1->release();
	digit2->release();
	digit3->release();

	workDigitStatuses retVal;

	int left = srcImage->cols;
	int right = 0;
	int leftSide = srcImage->cols;
	int rightSide = 0;
	std::vector<int> lines;
	bool twoDigits;

	static const float startingPercentage = 0.1;
	static const float endingPercentage = 0.9;
	static const float incrementalPercentage = 0.01;

	cutOffImageAboveAndBelowTheNumbers(srcImage);

	std::pair<int,int> linesBetweenDigits = getLinesBetweenDigits(srcImage);

	if(linesBetweenDigits.first == errorDetected)
	{
		retVal.digit1 = STATUS_UNABLE_TO_SEPARATE_NUMBERS;
		retVal.digit2 = STATUS_UNABLE_TO_SEPARATE_NUMBERS;
		retVal.digit3 = STATUS_UNABLE_TO_SEPARATE_NUMBERS;
		return retVal;
	}
	else
	{
		if(linesBetweenDigits.second == errorDetected)
		{
			twoDigits = true;
		}
		else
		{
			twoDigits = false;
		}
	}

	if(twoDigits)//2 digits
	{
		int middle = linesBetweenDigits.first;

		const float leftEdge = srcImage->cols*0.15;
		const float rightEdge = srcImage->cols*0.87;

		for(float mov = startingPercentage; mov <= endingPercentage; mov+=incrementalPercentage)
		{
			lines = horizontalScan(srcImage, mov);
			for(int i = 0; i < (int)lines.size(); i++)
			{
				if(lines[i] < leftSide && lines[i] > leftEdge)
				{
					leftSide = lines[i];
				}
				if(lines[i] > rightSide && lines[i] < rightEdge)
				{
					rightSide = lines[i];
				}
			}
		}

		//LEFT NUMBER
		right = middle;
		left = leftSide;
		cv::Mat croppedLeft(*srcImage, cv::Rect(left,0,right-left,srcImage->rows));
	    cropOutAlmostEmpty(&croppedLeft);
		*digit1 = std::move(croppedLeft);

		//RIGHT NUMBER
		right = rightSide;
		left = middle;
		cv::Mat croppedRight(*srcImage, cv::Rect(left,0,right-left,srcImage->rows));
	    cropOutAlmostEmpty(&croppedRight);
	    *digit2 = std::move(croppedRight);

	    if(digit1->empty())
	    {
	    	retVal.digit1 = STATUS_MISSING_NUMBER;
	    }
	    else
	    {
	    	retVal.digit1 = STATUS_FOUND_NUMBER;
	    }
		if(digit2->empty())
		{
	    	retVal.digit2 = STATUS_MISSING_NUMBER;
	    }
	    else
	    {
	    	retVal.digit2 = STATUS_FOUND_NUMBER;
	    }
	}
	else//3 digits
	{
		int middleLeft = linesBetweenDigits.first;
		int middleRight = linesBetweenDigits.second;

		const float leftEdge = srcImage->cols*0.15;
		const float rightEdge = srcImage->cols*0.90;

		for(float mov = startingPercentage; mov <= endingPercentage; mov+=incrementalPercentage)
		{
			lines = horizontalScan(srcImage, mov);
			for(int i = 0; i < (int)lines.size(); i++)
			{
				if(lines[i] < leftSide && lines[i] > leftEdge)
				{
					leftSide = lines[i];
				}
				if(lines[i] > rightSide && lines[i] < rightEdge)
				{
					rightSide = lines[i];
				}
			}
		}

		//LEFT NUMBER
		right = middleLeft;
		left = leftSide -1;//to show the line
		cv::Mat croppedLeft(*srcImage, cv::Rect(left,0,right-left,srcImage->rows));
	    cropOutAlmostEmptyLeftmost1(&croppedLeft);
	    *digit1 = std::move(croppedLeft);

		//CENTER NUMBER
		right = middleRight;
		left = middleLeft;
		cv::Mat croppedCenter(*srcImage, cv::Rect(left,0,right-left,srcImage->rows));
	    cropOutAlmostEmpty(&croppedCenter);
	    *digit2 = std::move(croppedCenter);

		//RIGHT NUMBER
		right = rightSide +1;//to show the line
		left = middleRight;
		cv::Mat croppedRight(*srcImage, cv::Rect(left,0,right-left,srcImage->rows));
	    cropOutAlmostEmptyRightmost0(&croppedRight);
	    *digit3 = std::move(croppedRight);

	    if(digit1->empty())
		{
			retVal.digit1 = STATUS_MISSING_NUMBER;
		}
		else
		{
			retVal.digit1 = STATUS_FOUND_NUMBER;
		}
		if(digit2->empty())
		{
			retVal.digit2 = STATUS_MISSING_NUMBER;
		}
		else
		{
			retVal.digit2 = STATUS_FOUND_NUMBER;
		}
		if(digit3->empty())
		{
			retVal.digit3 = STATUS_MISSING_NUMBER;
		}
		else
		{
			retVal.digit3 = STATUS_FOUND_NUMBER;
		}
	}

	return retVal;
}
