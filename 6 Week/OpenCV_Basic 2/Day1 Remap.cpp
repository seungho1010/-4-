#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image laod failed!" << endl;
		return -1;
	}

	int w = src.cols;
	int h = src.rows;

	// if you want resize -> change w, h
	// ex. 2x -> w *= 2, h *= 2

	Mat map1 = Mat::zeros(h, w , CV_32FC1);
	Mat map2 = Mat::zeros(h, w, CV_32FC1);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			map1.at<float>(y, x) = (float)y ;
			map2.at<float>(y, x) = (float)x; // point symmetry
			// map2.at<float>(y, x) = (float)y + 10 * sin(x / 32.f);
			//map2.at<float>(y, x) = (float)h - 1 - y; // flip
			//map2.at<float>(y, x) = (float)y/2; // resize
		}
	}

	Mat dst;
	remap(src, dst, map1, map2, INTER_LINEAR);
	//remap(src, dst, map1, map2, INTER_LINEAR, BORDER_DEFAULT);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
}
