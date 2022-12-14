#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	String filename = "lenna.bmp";
	Mat src = imread(filename, IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// Translate
	int dx = 50, dy = 100;

	// Method - 1
	Mat Trans_1 = Mat::zeros(src.size(), CV_8UC1);

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			int x_ = x + dx;
			int y_ = y + dy;
			if (x_ < 0 || x_ >= Trans_1.cols) continue;
			if (y_ < 0 || y_ >= Trans_1.rows) continue;
			Trans_1.at<uchar>(y_, x_) = src.at<uchar>(y, x);
}
	}
	// Method - 2
	Mat trans = (Mat_<float>(2, 3) << 1, 0, dx, 0, 1, dy);


	Mat Trans_2;
	warpAffine(src, Trans_2, trans, Size());


	imshow("src", src);
	String Trans_name = format("dst [x : %d, y : %d]", dx, dy);
	imshow(Trans_name, Trans_2);
	waitKey();
}
