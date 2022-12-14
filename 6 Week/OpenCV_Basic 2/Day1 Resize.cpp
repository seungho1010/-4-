#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void resizeBilinear(const Mat& src, Mat& dst, Size size);

int main()
{
	String filename = "camera.bmp";
	Mat src = imread(filename, IMREAD_GRAYSCALE);


	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// Resize

	// Simple method - 1
	// Not good (src * 2-> dst)
	int resize_x = 3, resize_y = 3;

	Mat Resize_1 = Mat::zeros(src.rows * resize_x, src.cols * resize_y, src.type());
	
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			int x_ = x * resize_x;
			int y_ = y * resize_y;

			Resize_1.at<uchar>(y_, x_) = src.at<uchar>(y, x);
		}
	}

	// Simple method - 2
	// (dst / 2-> src)

	Mat Resize_2 = Mat::zeros(src.rows * resize_x, src.cols * resize_y, src.type());

	for (int y_ = 0; y_ < Resize_1.rows; y_++) {
		for (int x_ = 0; x_ < Resize_1.cols; x_++) {
			int x = x_ / resize_x;
			int y = y_ / resize_y;
			Resize_2.at<uchar>(y_, x_) = src.at<uchar>(y, x);
		}
	}

	// Bilinear method
	Mat Resize_3;
	resizeBilinear(src, Resize_3, Size(src.rows * resize_x, src.cols * resize_y));

	// Use OpenCV function
	Mat dst1, dst2, dst3, dst4;
	resize_x = 10, resize_y = 10;


	TickMeter tm;

	tm.start();
	resize(src, dst1, Size(), resize_x, resize_y, INTER_NEAREST);
	tm.stop();
	double dst1_time = tm.getTimeMilli();
	tm.reset();
	tm.start();
	resize(src, dst2, Size(src.rows * resize_x, src.cols * resize_y));
	tm.stop();
	double dst2_time = tm.getTimeMilli();
	tm.reset();
	tm.start();
	resize(src, dst3, Size(src.rows * resize_x, src.cols * resize_y), 0, 0, INTER_CUBIC);
	tm.stop();
	double dst3_time = tm.getTimeMilli();
	tm.reset();
	tm.start();
	resize(src, dst4, Size(src.rows * resize_x, src.cols * resize_y), 0, 0, INTER_LANCZOS4);
	tm.stop();
	double dst4_time = tm.getTimeMilli();
	



	imshow("src", src);
	imshow("Resize - 1", Resize_1);
	imshow("Resize - 2", Resize_2);
	imshow("Bilinear method", Resize_3);

	String dst1_name = format("Inter Nearest, Time : %0.4fms", dst1_time);
	String dst2_name = format("Inter Linear, Time : %0.4fms", dst2_time);
	String dst3_name = format("Inter Cubic, Time : %0.4fms", dst3_time);
	String dst4_name = format("Inter Lanczos, Time : %0.4fms", dst4_time);
	imshow(dst1_name, dst1(Rect(400, 500, 400, 400)));
	imshow(dst2_name, dst2(Rect(400, 500, 400, 400)));
	imshow(dst3_name, dst3(Rect(400, 500, 400, 400)));
	imshow(dst4_name, dst4(Rect(400, 500, 400, 400)));
	waitKey();

	return 0;
}

void resizeBilinear(const Mat& src, Mat& dst, Size size)
{
	dst.create(size.height, size.width, CV_8U);

	int x1, y1, x2, y2;	double rx, ry, p, q, value;
	double sx = static_cast<double>(src.cols - 1) / (dst.cols - 1);
	double sy = static_cast<double>(src.rows - 1) / (dst.rows - 1);

	for (int y = 0; y < dst.rows; y++) {
		for (int x = 0; x < dst.cols; x++) {
			rx = sx * x;			ry = sy * y;
			x1 = cvFloor(rx);		y1 = cvFloor(ry);
			x2 = x1 + 1; if (x2 == src.cols) x2 = src.cols - 1;
			y2 = y1 + 1; if (y2 == src.rows) y2 = src.rows - 1;
			p = rx - x1;			q = ry - y1;

			value = (1. - p) * (1. - q) * src.at<uchar>(y1, x1)
				+ p * (1. - q) * src.at<uchar>(y1, x2)
				+ (1. - p) * q * src.at<uchar>(y2, x1)
				+ p * q * src.at<uchar>(y2, x2);

			dst.at<uchar>(y, x) = static_cast<uchar>(value + .5);
		}
	}
}