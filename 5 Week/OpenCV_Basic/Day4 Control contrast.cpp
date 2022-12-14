#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	String filename = "columbia.bmp";
	Mat src = imread(filename, IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	// Contrast control
	// Not use mean
	float alpha = 1.0f;
	Mat dst_128 = src + (src - 128) * alpha;

	// Use mean
	int m = (int)mean(src)[0];
	Mat dst_mean = src + (src - m) * alpha;

	// Mean -> 128, Contrast use 128
	Mat dst_ = src + (128 - m);
	dst_ = dst_ + (dst_ - 128) * alpha;


	String dst_mean_ = format("dst [mean : %d]", m);
	imshow("src", src);
	imshow("dst [mean : 128]", dst_128);
	imshow(dst_mean_, dst_mean);
	imshow("brightness -> contrast", dst_);

	waitKey();
}