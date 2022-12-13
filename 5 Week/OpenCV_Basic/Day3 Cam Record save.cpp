#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

// Load the video(*.mp4)
// Add the video size and FPS
// Save (*.avi)
int main(int argc, char* argv[])
{
	String filename = "road.mp4";

	// Open video file
	VideoCapture cap(filename);
	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return -1;
	}
	
	// Set video information
	int fourcc = VideoWriter::fourcc('X', 'V', 'I', 'D');

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);
	Size sz(w, h);

	VideoWriter output("output.avi", fourcc, cvRound(fps), sz);

	int delay = cvRound(1000 / fps);


	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) {
			cerr << "Empty frame!" << endl;
			break;
		}

		// Add video size and FPS
		String text = format("Size : %d x %d, FPS : %d", w, h, cvRound(fps));
		putText(frame, text, Point(50, 50), FONT_HERSHEY_SIMPLEX,
			0.7, Scalar(255, 255, 255), 2, LINE_AA);
		
		// Save frame
		output << frame;

		imshow("frame", frame);

		if (waitKey(delay) == 27)
			break;
	}

	cout << "output.avi file is created!!!" << endl;

	output.release();
	cap.release();
	destroyAllWindows();
}