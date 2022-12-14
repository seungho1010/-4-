#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void histogram_stretching_mod(const Mat& src, Mat& dst);
void histogram_stretching(const Mat& src, Mat& dst);
Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

int main(int argc, char* argv[])
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	resize(src, src, Size(src.rows * 2, src.cols * 2), 0, 0, INTER_CUBIC);
	Mat Hist_stretching, Hist_stretching_mod;

	histogram_stretching(src, Hist_stretching);
	histogram_stretching_mod(src, Hist_stretching_mod);

	imshow("Original", src);
	imshow("Hist Stretching", Hist_stretching);
	imshow("Hist Stretching modified", Hist_stretching_mod);


	Mat Hist_src = getGrayHistImage(calcGrayHist(src));
	Mat Hist_stretching_ = getGrayHistImage(calcGrayHist(Hist_stretching));
	Mat Hist_stretching_mod_ = getGrayHistImage(calcGrayHist(Hist_stretching_mod));

	imshow("Original_", Hist_src);
	imshow("Hist Stretching_", Hist_stretching_);
	imshow("Hist Stretching modified_", Hist_stretching_mod_);

	waitKey();
	return 0;
}

void histogram_stretching_mod(const Mat& src, Mat& dst)
{
	// Build histogram
	int hist[256] = {};
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			hist[src.at<uchar>(y, x)]++;
		}
	}

	// Set ratio_
	const float ratio_ = 0.01;
	int gmin = 255, gmax = 0;
	int ratio = int(src.cols * src.rows * ratio_);

	int size = (int)src.total();

	// calculate gmax
	for (int i = 0, s = 0; i < 255; i++) {
		s += hist[i];
		if (s > size - ratio)
		{
			gmax = i;
			break;
		}
	}

	// calculate gmin
	for (int i = 255, s = 0; i >= 0; i--) {
		s += hist[i];
		if (s > size - ratio)
		{
			gmin = i;
			break;
		}
	}

	dst = (src - gmin) * 255 / (gmax - gmin);
}

void histogram_stretching(const Mat& src, Mat& dst)
{
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	dst = (src - gmin) * 255 / (gmax - gmin);
}

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8U);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges, true);

	return hist;
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(!hist.empty());
	CV_Assert(hist.type() == CV_32F);

	double histMax = 0.;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}