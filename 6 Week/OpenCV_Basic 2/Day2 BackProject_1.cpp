#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	// Calculate CrCb histogram from a reference image

	Mat src = imread("cropland.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Rect rc = selectROI(src);

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat crop = src_ycrcb(rc);

	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	// �κ� ���� ���� ������׷� ���
	calcHist(&crop, 1, channels, Mat(), hist, 2, histSize, ranges);

	// ��ü ���� ���� ������׷� ������
	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges);

	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	src.copyTo(dst, backproj);

	//imshow("src", src);
	imshow("dst", dst);
	waitKey();
}
