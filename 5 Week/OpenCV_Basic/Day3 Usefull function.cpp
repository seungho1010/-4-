#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

string openCVType2str(int type);

int main(int argc, char* argv[])
{
	cout << "OpenCV Function" << endl;
	cout << endl;

	uchar data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat1(2, 3, CV_8UC1, data);

	int sum1 = (int)sum(mat1)[0];
	cout << "mat : " << mat1 << endl;
	cout << "sum(mat)[0] : " << sum1 << endl;
	cout << endl;
	
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);
	imshow("img", img);
	
	double mean1 = mean(img)[0];
	cout << "img = lenna.bmp" << endl;
	cout << "mean(img) : " << mean1 << endl;
	cout << endl;

	double minv, maxv;
	Point minLoc, maxLoc;

	minMaxLoc(img, &minv, &maxv, &minLoc, &maxLoc);
	cout << "minMaxLoc(img, &minv, &maxv, &minLoc, &maxLoc)" << endl;
	cout << "minv : " << minv << ", maxv : " << maxv << ", minLoc : " << minLoc << ", maxLoc : " << maxLoc << endl;
	cout << endl;

	Mat fimg;
	img.convertTo(fimg, CV_32FC1);
	cout << "img.converTo(fimg, CV_32FC1) -> fimg.type : " << openCVType2str(fimg.type()) << endl;
	cout << endl;

	Mat src = img;
	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX);
	imshow("normalize", dst);

	Mat img_color = imread("lenna.bmp");
	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	vector<Mat> planes;
	split(img_color, planes);
	swap(planes[0], planes[2]);

	Mat rgb;
	merge(planes, rgb);
	imshow("Red <-> Blue", rgb);

	TickMeter tm;
	tm.start();

	Mat canny;
	Canny(img_color, canny, 50, 100);
	cout << "Canny() time : " << tm.getTimeMilli() << "ms." << endl;
	tm.reset();

	waitKey(0);

}

string openCVType2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

