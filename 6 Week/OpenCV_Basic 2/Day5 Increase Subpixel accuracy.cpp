#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

const Point p1(300, 600), p2(500, 600); // Left Lane
const Point p3(800, 600), p4(1000, 600); // Right Lane

vector<Point2f> find_edges(const Mat& img);
void drawCross(Mat& img, Point pt, Scalar color);

int main()
{
	Mat src = imread("lane02.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image laod failed!" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	// ���� ���� �� ������ ���� ������ ���� �簢�� ����
	Rect rc1(p1 + Point(0, -10), p2 + Point(0, 10));
	Rect rc2(p3 + Point(0, -10), p4 + Point(0, 10));

	vector<Point2f> pts1 = find_edges(gray(rc1));
	vector<Point2f> pts2 = find_edges(gray(rc2));

	Mat dst = src.clone();
	line(dst, p1, p4, Scalar(0, 255, 128), 1, LINE_AA);

	// ���� ���� ��ġ ǥ��
	drawCross(dst, Point(cvRound(p1.x + pts1[0].x), p1.y), Scalar(255, 0, 0));
	drawCross(dst, Point(cvRound(p1.x + pts1[1].x), p1.y), Scalar(0, 0, 255));
	putText(dst, format("(%4.3f, %d)", p1.x + pts1[0].x, p1.y),
		Point(p1.x + pts1[0].x - 50, p1.y - 20),
		FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1, LINE_AA);
	putText(dst, format("(%4.3f, %d)", p1.x + pts1[1].x, p1.y),
		Point(p1.x + pts1[1].x - 20, p1.y + 30),
		FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);

	// ������ ���� ��ġ ǥ��
	drawCross(dst, Point(cvRound(p3.x + pts2[0].x), p3.y), Scalar(255, 0, 0));
	drawCross(dst, Point(cvRound(p3.x + pts2[1].x), p3.y), Scalar(0, 0, 255));
	putText(dst, format("(%4.3f, %d)", p3.x + pts2[0].x, p3.y),
		Point(p3.x + pts1[0].x - 50, p3.y - 20),
		FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1, LINE_AA);
	putText(dst, format("(%4.3f, %d)", p3.x + pts2[1].x, p3.y),
		Point(p3.x + pts1[1].x - 20, p3.y + 30),
		FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);

	imshow("dst", dst);
	waitKey();
}

// img ������ ���� ��ǥ �߰����� ���� ���� ������ ���۰� �� ��ǥ�� ����Ͽ� ��ȯ
vector<Point2f> find_edges(const Mat& img)
{
	// ����þ�, 1�� �̺� ���� ������ �Ǽ������� ������
	Mat fimg, blr, dx;
	img.convertTo(fimg, CV_32F);
	GaussianBlur(fimg, blr, Size(), 1.);
	Sobel(blr, dx, CV_32F, 1, 0);

	double minv, maxv;
	Point minloc, maxloc;

	int y2 = img.rows / 2;
	Mat roi = dx.row(y2);
	minMaxLoc(roi, &minv, &maxv, &minloc, &maxloc);

#if 0
	vector<Point2f> pts;
	pts.push_back(Point2f(maxloc.x, y2));
	pts.push_back(Point2f(minloc.x, y2));
#else
	// �����ȼ� ��Ȯ���� ���� ��ġ�� ã�� pts�� �����ϴ� �ڵ带 �ۼ��ϼ���!
	vector<Point2f> pts;
	float* ptr = roi.ptr<float>(0);

	float X, Y, Z;
	X = ptr[maxloc.x - 1];
	Y = ptr[maxloc.x];
	Z = ptr[maxloc.x + 1];

	pts.push_back(Point2f(maxloc.x + (X - Z) / (2 * X - 4 * Y + 2 * Z), y2));

	X = ptr[minloc.x - 1];
	Y = ptr[minloc.x];
	Z = ptr[minloc.x + 1];

	pts.push_back(Point2f(minloc.x + (X - Z) / (2 * X - 4 * Y + 2 * Z), y2));
#endif

	return pts;
}

void drawCross(Mat& img, Point pt, Scalar color)
{
	int span = 5;
	line(img, pt + Point(-span, -span), pt + Point(span, span), color, 1, LINE_AA);
	line(img, pt + Point(-span, span), pt + Point(span, -span), color, 1, LINE_AA);
}
