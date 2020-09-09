/*
 * img_prep.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "img_prep.h"
#include "opencv2/highgui.hpp"			//imshow
#include "opencv2/imgproc.hpp"			//cvtcolor,blur,resize,gauss...
#include "opencv2/imgproc/types_c.h"	//consts like COLOR_BGR2GRAY

enum retStatus{
	STATUS_OK = 0,
	STATUS_FILE_OPEN_ERROR = 1,
	STATUS_WRONG_SIZE_ERROR = 2
};

void increaseSaturation(cv::Mat* srcImage)
{
	const double alpha = 0.95; /**< Simple contrast control */
	const int beta = -5;  /**< Simple brightness control */

	//goes through every cell of the image matrix and edits the value
	for(int y = 0; y < srcImage->rows; y++ )
	{
		for(int x = 0; x < srcImage->cols; x++ )
		{
			//goes through every color of the of each pixel to edit it
			for(int c = 0; c < 3; c++ )
			{
				srcImage->at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>( alpha*( srcImage->at<cv::Vec3b>(y,x)[c] ) + beta );
			}
		}
	}
}

void blackWhiteIfy(cv::Mat* srcImage)
{
	//goes through every pixel of the image and sets the detected edge pixels to pure white
	for(int i = 0; i < srcImage->cols; i++)
	{
		for(int j = 0; j < srcImage->rows; j++)
		{
			if(srcImage->at<uchar>(j, i) > 0)
			{
				srcImage->at<uchar>(j, i) = 255;
			}
		}
	}
}

void CannyThreshold(cv::Mat* srcImage)
{
	//uses the Sobel operator in Canny function to extract edges from the image
	cv::Mat detected_edges;
	cv::Mat src_gray;
	const int cannyEdgeThreshold = 90; //0 - 100
	const int ratio = 3;
	const int kernel_size = 3;

	cv::cvtColor(*srcImage, src_gray, cv::COLOR_BGR2GRAY );
	cv::blur(src_gray, detected_edges, cv::Size(3,3) );
	Canny(detected_edges, detected_edges, cannyEdgeThreshold, cannyEdgeThreshold*ratio, kernel_size );
	*srcImage = cv::Scalar::all(0);//erases image
	src_gray.copyTo(*srcImage, detected_edges);
	blackWhiteIfy(srcImage);
}

int readImage(cv::Mat* srcImage, cv::String readImagePath)
{
	//tries to read the image from path into Mat variable
	static const int lowerThreshold = 295;
	static const int higherThreshold = 305;
	cv::Mat readImageImg = cv::imread(readImagePath, 1 );
	//returns error code if it can't read the image or the image is the wrong size
	if(readImageImg.empty())
	{
		return STATUS_FILE_OPEN_ERROR;
	}
	else if (readImageImg.cols < lowerThreshold
			|| readImageImg.cols > higherThreshold
			|| readImageImg.rows < lowerThreshold
			|| readImageImg.rows > higherThreshold)
	{
		return STATUS_WRONG_SIZE_ERROR;
	}
	*srcImage = std::move(readImageImg);
	return STATUS_OK;
}

int loadImage(cv::Mat* srcImage, cv::String readImagePath)
{
	int retVal = readImage(srcImage, readImagePath);
	if(retVal == STATUS_OK)
	{
		increaseSaturation(srcImage);
		CannyThreshold(srcImage);
	}
	return retVal;
}



