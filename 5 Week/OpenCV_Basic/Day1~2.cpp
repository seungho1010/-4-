#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

void learn_Point();
void learn_Rect();
void learn_Vec_Scalar();

int main(int argc, char* argv[])
{
	// 1 Day
	std::cout << "Day 1" << std::endl;
	std::cout << "OpenCV Version : " << CV_VERSION << std::endl;
	std::cout << std::endl;

	// 2 Day
	std::cout << "Day 2" << std::endl;

	// Point Class
	learn_Point();
	std::cout << std::endl;

	// Rect Class
	learn_Rect();
	std::cout << std::endl;

	// Vec, Scalar Class
	learn_Vec_Scalar();
}

void learn_Point()
{
	cv::Point pt1, pt2(4, 3), pt3(2, 4);
	int a = 2;

	std::cout << "pt2 : " << pt2 << ", pt3 : " << pt3 << std:: endl;
	std::cout << "pt2 + pt3  : " << pt2 +  pt3 << std::endl;
	std::cout << "pt2 - pt3  : " << pt2 - pt3 << std::endl;
	std::cout << "pt3 * 2  : " << pt2 * a << std::endl;
	std:: cout << "2 * pt3 : " << a * pt2 << std::endl;
	
	std::cout << "norm(pt2) : " << norm(pt2) << std::endl;
	
	bool b1, b2;
	b1 = pt1 == pt2;
	b2 = pt1 != pt2;

	std::cout << "pt1 == pt2 : " << b1 << std::endl;
	std::cout << "pt1 != pt2 : " << b2 << std::endl;
}

void learn_Rect()
{
	cv::Rect rc1;
	cv::Rect rc2(10, 10, 60, 40); //(x, y, w, h)

	std::cout << "rc2(10, 10, 60, 40) : " << rc2 << std::endl;

	cv::Rect rc3 = rc1 + cv::Size(50, 40);
	cv::Rect rc4 = rc2 + cv::Point(10, 10);
	cv::Rect rc5 = rc3 & rc4;
	cv::Rect rc6 = rc3 | rc4;

	std::cout << "rc3 = rc1 + Size(50, 40) -> " << rc3 << std::endl;
	std::cout << "rc4 = rc2 + Point(10, 10) -> " << rc4 << std::endl;
	std::cout << "rc5 = rc3 & rc4 -> " << rc5 << std::endl;
	std::cout << "rc6 = rc3 | rc4 -> " << rc6 << std::endl;
}

void learn_Vec_Scalar()
{
	cv::Scalar gray = 128;
	std::cout << "gray: " << gray << std::endl;

	cv::Scalar yellow(0, 255, 255);
	std::cout << "yellow: " << yellow << std::endl;

	for (int i = 0; i < 4; i++)
	{
		std::cout << yellow[i] << " ";
	}
	std::cout << std::endl;
}