/*
 * img_prep.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef IMG_PREP_H_
#define IMG_PREP_H_

#include "opencv2/core.hpp"				//Mat

enum loadStatus{
	STATUS_OK = 0,
	STATUS_FILE_OPEN_ERROR = 1,
	STATUS_WRONG_SIZE_ERROR = 2
};

//increases the saturation of the image
void increaseSaturation(cv::Mat* srcImage);

//turns all shades of non black pixels to white
void blackWhiteIfy(cv::Mat* srcImage);

//uses the canny function to get all the edges from the source image
void CannyThreshold(cv::Mat* srcImage);

//reads image from storage to memory
loadStatus readImage(cv::Mat* srcImage, cv::String readImagePath);

//prepares the loaded image for further use
//increases the saturation and draws out the edges
loadStatus loadImage(cv::Mat* srcImage, cv::String readImagePath);

#endif /* IMG_PREP_H_ */
