#include "img_prep.h"
#include "img_work.h"
#include "recognition.h"
#include "tests.h"
#include "opencv2/highgui.hpp"			//imshow
#include <iostream>						//cout

enum retStatus{
	STATUS_OK = 0,
	STATUS_FILE_OPEN_ERROR = 1,
	STATUS_WRONG_SIZE_ERROR = 2,
	STATUS_UNABLE_TO_SEPARATE_NUMBERS = 3,
	STATUS_MISSING_FIRST_NUMBER = 4,
	STATUS_MISSING_SECOND_NUMBER = 5,
	STATUS_MISSING_THIRD_NUMBER = 6,
	STATUS_MISSING_FIRST_AND_SECOND_NUMBERS = 7,
	STATUS_MISSING_FIRST_AND_THIRD_NUMBERS = 8,
	STATUS_MISSING_SECOND_AND_THIRD_NUMBERS = 9,
	STATUS_MISSING_ALL_NUMBERS = 10,

	STATUS_WRONG_FIRST_DIGIT = -1,
	STATUS_WRONG_SECOND_DIGIT = -2,
	STATUS_WRONG_THIRD_DIGIT = -3,
	STATUS_WRONG_FIRST_AND_SECOND_DIGITS = -4,
	STATUS_WRONG_FIRST_AND_THIRD_DIGITS = -5,
	STATUS_WRONG_SECOND_AND_THIRD_DIGITS = -6,
	STATUS_WRONG_EVERY_DIGIT = -7,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT = -8,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT = -9,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT = -10,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_SECOND_DIGITS = -11,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_THIRD_DIGITS = -12,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_AND_THIRD_DIGITS = -13,
	STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_EVERY_DIGIT = -14,
	STATUS_WRONG_FIRST_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT = -15,
	STATUS_WRONG_FIRST_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT = -16,
	STATUS_WRONG_FIRST_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_AND_THIRD_DIGITS = -17,
	STATUS_WRONG_SECOND_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT = -18,
	STATUS_WRONG_SECOND_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT = -19,
	STATUS_WRONG_SECOND_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_THIRD_DIGITS = -20,
	STATUS_WRONG_THIRD_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT = -21,
	STATUS_WRONG_THIRD_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT = -22,
	STATUS_WRONG_THIRD_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_SECOND_DIGITS = -23,
	STATUS_WRONG_FIRST_AND_SECOND_DIGITS_AND_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT = -24,
	STATUS_WRONG_FIRST_AND_THIRD_DIGITS_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT = -25,
	STATUS_WRONG_SECOND_AND_THIRD_DIGITS_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT = -26
};

cv::Mat srcImage;
cv::Mat digit1;
cv::Mat digit2;
cv::Mat digit3;

int main( int argc, char** argv )
{
	for(int i = 1; i < argc; i++)
	{
		clock_t tStart = clock();

		cv::String imageLocation = argv[i];
		std::cout << imageLocation << std::endl;
		if(!imageLocation.compare("-test"))
		{
			testAll(&digit1, &digit2, &digit3);
		}
		else if(!imageLocation.compare("-digits_on"))
		{
			setWriteOutDigits(true);
		}
		else if(!imageLocation.compare("-digits_off"))
		{
			setWriteOutDigits(false);
		}
		else
		{
			int retStatus = loadImage(&srcImage, imageLocation);
			if(retStatus != STATUS_OK)
			{
				if(retStatus == STATUS_FILE_OPEN_ERROR)
				{
					std::cout << "Could not open or find the image!" << std::endl;
					std::cout << "Path: " << imageLocation << std::endl;
				}
				else if(retStatus == STATUS_WRONG_SIZE_ERROR)
				{
					std::cout << "Wrong size of the image!" << std::endl;
					std::cout << "Path: " << imageLocation << std::endl;
				}
			}
			else
			{
				retStatus = getDigits(&srcImage, &digit1, &digit2, &digit3);
				if(retStatus > 0)
				{
					switch(retStatus)
					{
						case STATUS_UNABLE_TO_SEPARATE_NUMBERS:
						{
							std::cout << "Unable to separate numbers" << std::endl;
						}
						break;
						case STATUS_MISSING_FIRST_NUMBER:
						{
							std::cout << "Can't find FIRST number" << std::endl;
						}
						break;
						case STATUS_MISSING_SECOND_NUMBER:
						{
							std::cout << "Can't find SECOND number" << std::endl;
						}
						break;
						case STATUS_MISSING_THIRD_NUMBER:
						{
							std::cout << "Can't find THIRD number" << std::endl;
						}
						break;
						case STATUS_MISSING_FIRST_AND_SECOND_NUMBERS:
						{
							std::cout << "Can't find FIRST and SECOND numbers" << std::endl;
						}
						break;
						case STATUS_MISSING_FIRST_AND_THIRD_NUMBERS:
						{
							std::cout << "Can't find FIRST and THIRD numbers" << std::endl;
						}
						break;
						case STATUS_MISSING_SECOND_AND_THIRD_NUMBERS:
						{
							std::cout << "Can't find SECOND and THIRD numbers" << std::endl;
						}
						break;
						case STATUS_MISSING_ALL_NUMBERS:
						{
							std::cout << "Can't find ANY number" << std::endl;
						}
						break;
					}
				}
				else
				{
					retStatus = detectNumbers(&digit1, &digit2, &digit3);
					if(retStatus < 0)
					{
						switch(retStatus)
						{
						case STATUS_WRONG_FIRST_DIGIT:
						{
							std::cout << "Can't recognize FIRST digit" << std::endl;
						}
						break;
						case STATUS_WRONG_SECOND_DIGIT:
						{
							std::cout << "Can't recognize SECOND digit" << std::endl;
						}
						break;
						case STATUS_WRONG_THIRD_DIGIT:
						{
							std::cout << "Can't recognize THIRD digit" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_AND_SECOND_DIGITS:
						{
							std::cout << "Can't recognize FIRST and SECOND digits" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_AND_THIRD_DIGITS:
						{
							std::cout << "Can't recognize FIRST and THIRD digits" << std::endl;
						}
						break;
						case STATUS_WRONG_SECOND_AND_THIRD_DIGITS:
						{
							std::cout << "Can't recognize SECOND and THIRD digits" << std::endl;
						}
						break;
						case STATUS_WRONG_EVERY_DIGIT:
						{
							std::cout << "Can't recognize ANY digit" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT:
						{
							std::cout << "Multiple numbers detected in FIRST digit" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT:
						{
							std::cout << "Multiple numbers detected in SECOND digit" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT:
						{
							std::cout << "Multiple numbers detected in THIRD digit" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_SECOND_DIGITS:
						{
							std::cout << "Multiple numbers detected in FIRST and SECOND digits" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_THIRD_DIGITS:
						{
							std::cout << "Multiple numbers detected in FIRST and THIRD digits" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_AND_THIRD_DIGITS:
						{
							std::cout << "Multiple numbers detected in SECOND and THIRD digits" << std::endl;
						}
						break;
						case STATUS_MULTIPLE_NUMBERS_DETECTED_FOR_EVERY_DIGIT:
						{
							std::cout << "Multiple numbers detected in EVERY digit" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT:
						{
							std::cout << "Can't recognize FIRST digit and multiple numbers detected in SECOND digit" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT:
						{
							std::cout << "Can't recognize FIRST digit and multiple numbers detected in THIRD digit" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_AND_THIRD_DIGITS:
						{
							std::cout << "Can't recognize FIRST digit and multiple numbers detected in SECOND and THIRD digits" << std::endl;
						}
						break;
						case STATUS_WRONG_SECOND_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT:
						{
							std::cout << "Can't recognize SECOND digit and multiple numbers detected in FIRST digit" << std::endl;
						}
						break;
						case STATUS_WRONG_SECOND_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT:
						{
							std::cout << "Can't recognize SECOND digit and multiple numbers detected in THIRD digit" << std::endl;
						}
						break;
						case STATUS_WRONG_SECOND_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_THIRD_DIGITS:
						{
							std::cout << "Can't recognize SECOND digit and multiple numbers detected in FIRST AND THIRD digits" << std::endl;
						}
						break;
						case STATUS_WRONG_THIRD_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT:
						{
							std::cout << "Can't recognize THIRD digit and multiple numbers detected in FIRST digit" << std::endl;
						}
						break;
						case STATUS_WRONG_THIRD_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT:
						{
							std::cout << "Can't recognize THIRD digit and multiple numbers detected in SECOND digit" << std::endl;
						}
						break;
						case STATUS_WRONG_THIRD_DIGIT_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_AND_SECOND_DIGITS:
						{
							std::cout << "Can't recognize THIRD digit and multiple numbers detected in FIRST and SECOND digits" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_AND_SECOND_DIGITS_AND_MULTIPLE_NUMBERS_DETECTED_FOR_THIRD_DIGIT:
						{
							std::cout << "Can't recognize FIRST and SECOND digits and multiple numbers detected in THIRD digit" << std::endl;
						}
						break;
						case STATUS_WRONG_FIRST_AND_THIRD_DIGITS_AND_MULTIPLE_NUMBERS_DETECTED_FOR_SECOND_DIGIT:
						{
							std::cout << "Can't recognize SECOND and THIRD digits and multiple numbers detected in SECOND digit" << std::endl;
						}
						break;
						case STATUS_WRONG_SECOND_AND_THIRD_DIGITS_AND_MULTIPLE_NUMBERS_DETECTED_FOR_FIRST_DIGIT:
						{
							std::cout << "Can't recognize SECOND and THIRD digits and multiple numbers detected in FIRST digit" << std::endl;
						}
						break;
						}
					}
					else
					{
						std::cout << "Detected number = " << retStatus << std::endl;
						imshow(imageLocation, srcImage);
						if(!digit1.empty())
						{
							imshow("digit1 "+imageLocation, digit1);
						}
						if(!digit2.empty())
						{
							imshow("digit2 "+imageLocation, digit2);
						}
						if(!digit3.empty())
						{
							imshow("digit3 "+imageLocation, digit3);
						}
					}
				}
			}
		}

		std::cout << "Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC*1000 << "ms" << std::endl;
	}

	std::cout << "Happy End!" << std::endl;
	cv::waitKey(0);
	return 0;
}
