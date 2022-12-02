#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Usage: ocvrt.exe <src_image> <dst_image>" << endl;
		return 0;
	}

	// read alpha channel
	Mat img = imread(argv[1], IMREAD_UNCHANGED);

	if (img.empty())
	{
		cerr << "Image Load Failed!" << endl;
		return -1;
	}

	bool is_saved = imwrite(argv[2], img);

	if (is_saved)
	{
		cout << argv[1] << " is successfully saved as " << argv[2] << endl;
	}
	else
	{
		cout << "File save failed!" << endl;
	}
	
	return 0;
}