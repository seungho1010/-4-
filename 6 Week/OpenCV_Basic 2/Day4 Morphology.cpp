#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
	Mat src = imread("rice.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// ���� ����ȭ
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC1);
	int bw = src.cols / 4;
	int bh = src.rows / 4;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			Mat src_ = src(Rect(x * bw, y * bh, bw, bh));
			Mat dst_ = dst(Rect(x * bw, y * bh, bw, bh));
			threshold(src_, dst_, 0, 255, THRESH_BINARY | THRESH_OTSU);
		}
	}

	// ���̺� �Լ��� �̿��� ��� ��ü ���� ���ϱ�
	Mat labels;

	int cnt1 = connectedComponents(dst, labels);
	cout << "# of objects in dst: " << cnt1 - 1 << endl;

	Mat dst2;
	morphologyEx(dst, dst2, MORPH_OPEN, Mat()); // erode(dst, dst2, Mat()), dilate(dst2, dst2, Mat());
	morphologyEx(dst2, dst2, MORPH_CLOSE, Mat());

	int cnt2 = connectedComponents(dst2, labels);
	cout << "# of objects in dst2: " << cnt2 - 1 << endl;

	imshow("src", src);
	imshow("dst", dst);
	imshow("dst2", dst2);
	waitKey();
}
