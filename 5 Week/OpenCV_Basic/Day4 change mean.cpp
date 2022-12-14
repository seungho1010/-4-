#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	String filename = "columbia.bmp";

	Mat src = imread(filename, IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	// Calculate Mean - Method 1
	int s = 0;
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			s += src.at<uchar>(y, x);
		}
	}

	int m = s / (src.rows * src.cols);
	
	// Calculate Mean - Method 2
	//int m = sum(src)[0] / src.total();
	
	// Calculate Mean - Method 3
	//int m = mean(src)[0];

	cout << "Mean value: " << m << endl;

	// Mean -> 128
	Mat dst = src + (128 - m);

	String src_name = format("src(Mean : %d)", m);
	imshow(src_name, src);
	imshow("dst(Mean : 128)", dst);

	waitKey();
}