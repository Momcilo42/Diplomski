/*
 * img_prep.h
 *
 *  Created on: Jun 4, 2020
 *      Author: momcilo
 */

#ifndef IMG_PREP_H_
#define IMG_PREP_H_

#include "opencv_dependencies.h"

using namespace cv;

//increases the saturation of the image
void increaseSaturation(Mat* srcImage);

//turns all shades of non black pixels to white
void blackWhiteIfy(Mat* srcImage);

//uses the canny function to get all the edges from the source image
void CannyThreshold(Mat* srcImage);

//reads image from storage to memory
void readImage(Mat* srcImage, String readImagePath);

//prepares the loaded image for further use
//increases the saturation and draws out the edges
void loadImage(Mat* srcImage, String readImagePath);

#endif /* IMG_PREP_H_ */
