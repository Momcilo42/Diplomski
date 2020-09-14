#include "img_prep.h"
#include "img_work.h"
#include "recognition.h"
#include "print.h"
#include "tests.h"
#include "opencv2/highgui.hpp"			//imshow

cv::Mat srcImage;
cv::Mat digit1;
cv::Mat digit2;
cv::Mat digit3;

static bool writeOutDigits = true;

int main( int argc, char** argv )
{
	for(int i = 1; i < argc; i++)
	{
		clock_t tStart = clock();

		cv::String imageLocation = argv[i];
		std::cout << imageLocation << std::endl;
		if(!imageLocation.compare("-test"))
		{
			testAll(&digit1, &digit2, &digit3, writeOutDigits);
		}
		else if(!imageLocation.compare("-digits_on"))
		{
			writeOutDigits = true;
		}
		else if(!imageLocation.compare("-digits_off"))
		{
			writeOutDigits = false;
		}
		else
		{
			loadStatus retLoadStatus = loadImage(&srcImage, imageLocation);
			if(retLoadStatus != STATUS_OK)
			{
				writeOutLoadErrors(&retLoadStatus, &imageLocation);
			}
			else
			{
				workDigitStatuses retWorkStatuses = getDigits(&srcImage, &digit1, &digit2, &digit3);
				writeOutWorkErrors(&retWorkStatuses, &digit1, &digit2, &digit3);

				detectedNumber retDetectedNumber = detectNumbers(&digit1, &digit2, &digit3);
				writeOutDetectedErrors(&retDetectedNumber);

				if(writeOutDigits)
				{
					printOutDigits(&retDetectedNumber, writeOutDigits);
				}

				printOutFullNumber(&retDetectedNumber, &digit1, &digit2, &digit3);

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

		std::cout << "Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC*1000 << "ms" << std::endl;
	}

	std::cout << "Happy End!" << std::endl;
	cv::waitKey(0);
	return 0;
}
