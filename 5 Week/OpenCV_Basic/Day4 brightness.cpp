#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	int brightness = 50;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// Method 1
	Mat Method_1(src.rows, src.cols, src.type());
	Method_1 = src + brightness;

	//  Method 2
	Mat Method_2(src.rows, src.cols, src.type());

	for (int y= 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			// int v = src.at<uchar>(y, x) - brightness;
			// v = (v > 255) ? : 255 : (v < 0) ? 0 : v;
			// Method_2.at<uchar>(
			Method_2.at<uchar>(y, x) = saturate_cast<uchar>(src.at<uchar>(y, x) + brightness);
		}
	}

	imshow("src", src);
	imshow("Method 1", Method_1);
	imshow("Method 2", Method_2);
	waitKey();
}