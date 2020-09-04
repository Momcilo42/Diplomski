#include "img_prep.h"
#include "img_work.h"
#include "recognition.h"
#include "tests.h"

using namespace std;
using namespace cv;

Mat srcImage;
Mat digit1;
Mat digit2;
Mat digit3;

int main( int argc, char** argv )
{
	for(int i = 1; i < argc; i++)
	{
		clock_t tStart = clock();

		String imageLocation = argv[i];
		cout << imageLocation << endl;
		if(!imageLocation.compare("-test"))
		{
			testAll(&digit1, &digit2, &digit3);
		}
		else
		{
			loadImage(&srcImage, imageLocation);
			if(srcImage.empty())
			{
				cout << "Error with image" << endl;
			}
			else
			{
				getDigits(&srcImage, &digit1, &digit2, &digit3);
				detectNumbers(&digit1, &digit2, &digit3);

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

		cout << "Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC*1000 << "ms" << endl;
	}

	std::cout << "Happy End!" << std::endl;
	waitKey(0);
	return 0;
}
