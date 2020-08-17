/*
 * img_prep.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#include "img_prep.h"

void increaseSaturation(Mat* srcImage)
{
	double alpha = 0.95; /**< Simple contrast control */ //alpha value [1.0-3.0]
	int beta = -5;  /**< Simple brightness control */ 	//beta value [0-100]

	for(int y = 0; y < srcImage->rows; y++ )
		for(int x = 0; x < srcImage->cols; x++ )
			for(int c = 0; c < 3; c++ )
				srcImage->at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( srcImage->at<Vec3b>(y,x)[c] ) + beta );
}

void blackWhiteIfy(Mat* srcImage)
{
	for(int i = 0; i < srcImage->cols; i++)
		for(int j = 0; j < srcImage->rows; j++)
			if(srcImage->at<uchar>(j, i) > 0)
				srcImage->at<uchar>(j, i) = 255;
}

void CannyThreshold(Mat* srcImage)
{
	Mat detected_edges;
	Mat src_gray;
	const int cannyEdgeThreshold = 90; //0 - 100
	const int ratio = 3;
	const int kernel_size = 3;

	cvtColor(*srcImage, src_gray, COLOR_BGR2GRAY );
	blur(src_gray, detected_edges, Size(3,3) );
	Canny(detected_edges, detected_edges, cannyEdgeThreshold, cannyEdgeThreshold*ratio, kernel_size );
	*srcImage = Scalar::all(0);//erases image
	src_gray.copyTo(*srcImage, detected_edges);
	blackWhiteIfy(srcImage);
}

void readImage(Mat* srcImage, String readImagePath)
{
	Mat readImageImg = imread(readImagePath, 1 );
	if(readImageImg.empty())
	{
		std::cout << "Could not open or find the image!" << std::endl;
		std::cout << "Usage: " << readImagePath << " <Input image>" << std::endl;
		exit(1);
	}
	if (readImageImg.cols < 295
			|| readImageImg.cols > 305
			|| readImageImg.rows < 295
			|| readImageImg.rows > 305)
	{
		std::cout << "Wrong size of the image!" << std::endl;
		std::cout << "Usage: " << readImagePath << " <Input image>" << std::endl;
		exit(1);
	}
	*srcImage = readImageImg;
}

void loadImage(Mat* srcImage, String readImagePath)
{
	readImage(srcImage, readImagePath);
	increaseSaturation(srcImage);
	CannyThreshold(srcImage);
}



