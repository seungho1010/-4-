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

	// Shear
	bool dir = 0; // x direction = 0, y direction = 1
	double m = 0.2; // 0 ~ 1

	// Method - 1
	Mat Shear_1(src.rows * 2, src.cols * 2, src.type(), Scalar(0));

	if (dir == 0) {
		for (int y = 0; y < src.rows; y++) {
			for (int x = 0; x < src.cols; x++) {
				int nx = int(x + m * y);
				int ny = y;
				Shear_1.at<uchar>(ny, nx) = src.at<uchar>(y, x);
			}
		}
	}
	else {
		for (int y = 0; y < src.rows; y++) {
			for (int x = 0; x < src.cols; x++) {
				int nx = x;
				int ny = int(y + m * x);
				Shear_1.at<uchar>(ny, nx) = src.at<uchar>(y, x);
			}
		}
	}
	
	// Method - 2
	Mat shear;
	if (dir == 0) {
		shear = (Mat_<float>(2, 3) << 1, m, 0, 0, 1, 0);
	}
	else {
		shear = (Mat_<float>(2, 3) << 1, 0, 0, m, 1, 0);
	}
	Mat Shear_2;
	warpAffine(src, Shear_2, shear, Size(src.cols * 2, src.rows * 2));


	String Shear_name;
	if (dir == 0)
		Shear_name = format("dst - shear[x : %.2f]", m);
	else
		Shear_name = format("dst - shear[y : %.2f]", m);

	imshow("src", src);
	imshow(Shear_name ,Shear_2);

	waitKey();
}