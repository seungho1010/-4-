#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void myCanny(const cv::Mat& src, cv::Mat& dst, double threshold1, double threshold2);

int main()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat dst1, dst2;
	Canny(src, dst1, 50, 150); // low : high = 1 : 2 or 1: 3
	myCanny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("OpenCV Canny", dst1);
	imshow("My Canny", dst2);

	waitKey();
}

void myCanny(const Mat& src, Mat& dst, double threshold1, double threshold2)
{
	// 1. Gaussian filter
	Mat gauss;
	GaussianBlur(src, gauss, Size(), 0.5);

	// 2. Gradient by Sobel operator
	Mat dx, dy;
	Sobel(gauss, dx, CV_32F, 1, 0);
	Sobel(gauss, dy, CV_32F, 0, 1);

	Mat mag = Mat::zeros(src.rows, src.cols, CV_32F);
	Mat ang = Mat::zeros(src.rows, src.cols, CV_32F);

	for (int y = 0; y < src.rows; y++) {
		float* pDx = dx.ptr<float>(y);
		float* pDy = dy.ptr<float>(y);
		float* pMag = mag.ptr<float>(y);
		float* pAng = ang.ptr<float>(y);

		for (int x = 0; x < src.cols; x++) {
			// mag�� �׷����Ʈ�� ũ��
			pMag[x] = sqrt(pDx[x] * pDx[x] + pDy[x] * pDy[x]);

			// ang�� �׷����Ʈ�� ���� (���� ���� �ް��ϰ� ���ϴ� ����)
			if (pDx[x] == 0)
				pAng[x] = 90.f;
			else
				pAng[x] = float(atan(pDy[x] / pDx[x]) * 180 / CV_PI);
		}
	}

	// 3. Non-maximum suppression
	enum DISTRICT { AREA0 = 0, AREA45, AREA90, AREA135, NOAREA };
	const int ang_array[] = { AREA0, AREA45, AREA45, AREA90, AREA90, AREA135, AREA135, AREA0 };

	const uchar STRONG_EDGE = 255;
	const uchar WEAK_EDGE = 128;

	vector<Point> strong_edges;
	dst = Mat::zeros(src.rows, src.cols, CV_8U);

	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			// �׷����Ʈ ũ�Ⱑ th_low���� ū �ȼ��� ���ؼ��� ������ �ִ� �˻�.
			// ������ �ִ��� �ȼ��� ���ؼ��� ���� ���� �Ǵ� ���� ������ ����.
			float mag_value = mag.at<float>(y, x);
			if (mag_value > threshold1) {
				// �׷����Ʈ ���⿡ 90���� ���Ͽ� ������ ������ ��� (4�� ����)
				int ang_idx = cvFloor((ang.at<float>(y, x) + 90) / 22.5f);

				// ������ �ִ� �˻�
				bool local_max = false;
				switch (ang_array[ang_idx]) {
				case AREA0:
					if ((mag_value >= mag.at<float>(y - 1, x)) && (mag_value >= mag.at<float>(y + 1, x))) {
						local_max = true;
					}
					break;
				case AREA45:
					if ((mag_value >= mag.at<float>(y - 1, x + 1)) && (mag_value >= mag.at<float>(y + 1, x - 1))) {
						local_max = true;
					}
					break;
				case AREA90:
					if ((mag_value >= mag.at<float>(y, x - 1)) && (mag_value >= mag.at<float>(y, x + 1))) {
						local_max = true;
					}
					break;
				case AREA135:
				default:
					if ((mag_value >= mag.at<float>(y - 1, x - 1)) && (mag_value >= mag.at<float>(y + 1, x + 1))) {
						local_max = true;
					}
					break;
				}

				// ���� ������ ���� ���� ����.
				if (local_max) {
					if (mag_value > threshold2) {
						dst.at<uchar>(y, x) = STRONG_EDGE;
						strong_edges.push_back(Point(x, y));
					}
					else {
						dst.at<uchar>(y, x) = WEAK_EDGE;
					}
				}
			}
		}
	}
	// dst -> String edge -> black, Weak edge -> gray

#define CHECK_WEAK_EDGE(x, y) \
	if (dst.at<uchar>(y, x) == WEAK_EDGE) { \
		dst.at<uchar>(y, x) = STRONG_EDGE; \
		strong_edges.push_back(Point(x, y)); \
	}

	// 4. Hysterisis edge tracking
	while (!strong_edges.empty()) {
		Point p = strong_edges.back();
		strong_edges.pop_back();

		// ���� ���� �ֺ��� ���� ������ ���� ����(���� ����)�� ����
		CHECK_WEAK_EDGE(p.x + 1, p.y)
		CHECK_WEAK_EDGE(p.x + 1, p.y + 1)
		CHECK_WEAK_EDGE(p.x, p.y + 1)
		CHECK_WEAK_EDGE(p.x - 1, p.y + 1)
		CHECK_WEAK_EDGE(p.x - 1, p.y)
		CHECK_WEAK_EDGE(p.x - 1, p.y - 1)
		CHECK_WEAK_EDGE(p.x, p.y - 1)
		CHECK_WEAK_EDGE(p.x + 1, p.y - 1)
	}

	// ������ ���� ������ �����ִ� �ȼ��� ��� ������ �ƴ� ������ �Ǵ�.
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			if (dst.at<uchar>(y, x) == WEAK_EDGE)
				dst.at<uchar>(y, x) = 0;
		}
	}
}
