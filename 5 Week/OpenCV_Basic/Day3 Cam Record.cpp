#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <typeinfo>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	// Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();

    const auto window_name = "Display Image";
    namedWindow(window_name, WINDOW_AUTOSIZE);

    bool is_first = 1;
    double old_timestampe, new_timestampe;
    double time_diff;

    while (true)
    {
        rs2::frameset data = pipe.wait_for_frames();
        rs2::frame image = data.get_color_frame();
        
        if (is_first == 1) {
            new_timestampe = data.get_timestamp();
            is_first = 0;
        }
        else {
            new_timestampe = data.get_timestamp();
            time_diff = new_timestampe - old_timestampe; // ms
        }

        // Query frame size (width and height)
        const int w = image.as<rs2::video_frame>().get_width();
        const int h = image.as<rs2::video_frame>().get_height();
     
        // Create OpenCV matrix of size (w,h) from the colorized depth data
        Mat img(Size(w, h), CV_8UC3, (void*)image.get_data(), Mat::AUTO_STEP);

        vector<Mat> planes;
        split(img, planes);

        // for RGB -> BGR
        swap(planes[0], planes[2]);
        
        Mat dst;
        merge(planes, dst);

        Mat edge;
        Canny(dst, edge, 50, 150);

        String text = format("%d x %d, FPS: %.0f", w, h, 1000/time_diff);
        putText(dst, text, Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 2, LINE_AA);

        imshow(window_name, dst);
        imshow("edge", edge);

        old_timestampe = new_timestampe;

        if (waitKey(1) == 27)
            break;
    }

	return 0;
}