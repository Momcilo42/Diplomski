/*
 * img_prep.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef IMG_PREP_H_
#define IMG_PREP_H_

#include <iostream>						//cout
#include "opencv2/highgui.hpp"			//imshow
#include "opencv2/imgproc.hpp"			//cvtcolor,blur,resize,gauss...
#include "opencv2/imgproc/types_c.h"	//consts like COLOR_BGR2GRAY

//increases the saturation of the image
void increaseSaturation(cv::Mat* srcImage);

//turns all shades of non black pixels to white
void blackWhiteIfy(cv::Mat* srcImage);

//uses the canny function to get all the edges from the source image
void CannyThreshold(cv::Mat* srcImage);

//reads image from storage to memory
void readImage(cv::Mat* srcImage, cv::String readImagePath);

//prepares the loaded image for further use
//increases the saturation and draws out the edges
void loadImage(cv::Mat* srcImage, cv::String readImagePath);

#endif /* IMG_PREP_H_ */
