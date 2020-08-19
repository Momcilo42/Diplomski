
#ifndef DEPENDENCIES
#define DEPENDENCIES

#include "opencv_dependencies.h"

#endif

#include "img_prep.h"
#include "img_work.h"
#include "recognition.h"
#include "tests.h"

Mat* srcImage = new Mat();
Mat* digit1 = new Mat();
Mat* digit2 = new Mat();
Mat* digit3 = new Mat();

int main( int argc, char** argv )
{
	for(int i = 1; i < argc; i++)
	{
		clock_t tStart = clock();

		String imageLocation = argv[i];
		cout << imageLocation << endl;
		if(!imageLocation.compare("-test"))
		{
			testAll(digit1, digit2, digit3);
		}
		else
		{
			loadImage(srcImage, imageLocation);
			if(srcImage->empty())
			{
				cout << "Error with image" << endl;
			}
			else
			{
				getNumbers(srcImage, digit1, digit2, digit3);
				const Mat* newDigit1 = new Mat(*digit1);
				const Mat* newDigit2 = new Mat(*digit2);
				const Mat* newDigit3 = new Mat(*digit3);
				detectNumbers(newDigit1, newDigit2, newDigit3);

				imshow(imageLocation, *srcImage);
				if(!digit1->empty())
				{
					imshow("digit1 "+imageLocation, *digit1);
				}
				if(!digit2->empty())
				{
					imshow("digit2 "+imageLocation, *digit2);
				}
				if(!digit3->empty())
				{
					imshow("digit3 "+imageLocation, *digit3);
				}
			}
		}

		cout << "Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC*1000 << "ms" << endl;
	}

	std::cout << "Happy End!" << std::endl;
	waitKey(0);
	return 0;
}
