#include <iostream>
#include <cmath>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

// Mouse Left button
// : draw red dot
// Mouse Right button
// : draw blue circle
// Trackbar
// : adjust brightness

Mat src;
Point ptOld, ptNew;
void on_mouse(int event, int x, int y, int flags, void*);
void on_level_change(int pos, void* userdata);

int main(void)
{
	src = imread("lenna.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("src");
	setMouseCallback("src", on_mouse);
	createTrackbar("level", "src", 0, 10, on_level_change, (void*)&src);

	imshow("src", src);
	waitKey();
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	// Draw red dot
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		break;
	case EVENT_LBUTTONUP:
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			cout << event << endl;
			line(src, ptOld, Point(x, y), Scalar(0, 0, 255), 3, LINE_AA);
			ptOld = Point(x, y);
			imshow("src", src);
		}
		break;
	// Draw blue circle
	case EVENT_RBUTTONDOWN:
		ptOld = Point(x, y);
		break;
	case EVENT_RBUTTONUP:
		ptNew = Point(x, y);
		circle(src, ptOld, sqrt(pow((ptOld.x - ptNew.x), 2) + pow((ptOld.y - ptNew.y), 2)), Scalar(255, 0, 0), 3, LINE_AA);
		imshow("src", src);
		break;
	default:
		break;
	}
}

void on_level_change(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;

	Mat white(img.cols, img.rows, CV_8UC3);
	Mat dst;

	double ratio = (double)pos / 10;

	addWeighted(src, (1-ratio), white, ratio, 0.0, dst);
	imshow("src", dst);
}