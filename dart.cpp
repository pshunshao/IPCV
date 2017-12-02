#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"


using namespace std;
using namespace cv;



String cascade_name = "cascade.xml";
CascadeClassifier cascade;
const int intesect_threshold = 4;




bool search_hough_line(Mat frame, Rect dartR) {
	Rect rect(dartR.x, dartR.y, dartR.width, dartR.height);
	Mat frame_gray;
	Mat edges;
	Mat img;
	std::vector<Vec4i> lines;
	Canny(frame_gray, img, 100, 200, 3);
	img(rect).copyTo(edges);
	Mat intersect = Mat(edges.cols, edges.rows, CV_32FC1, Scalar::all(0));
	HoughLines(edges, lines, 1, CV_PI / 180, 50, 0, 0);
	for (size_t k = 0; k< lines.size(); k++) {
		float rho = lines[k][0], theta = lines[k][1];
		Point p1, p2;
		p1.x = 0;
		p1.y = (rho - (p1.x - edges.cols / 2)  * cos(theta)) / sin(theta) + edges.rows / 2;
		p2.x = lines.size();
		p2.y = (rho - (p2.x - edges.cols / 2) * cos(theta)) / sin(theta) + edges.rows / 2;
		double m = -cos(theta) / sin(theta), c = rho / sin(theta);
		for (int i = 0; i< intersect.cols; i++) {
			for (int j = 0; j<intersect.rows; j++) {
				if (j == cvRound(m*i + rho / sin(theta))) {
					intersect.at<float>(i, j)++;
				}
			}
		}

	}
	float max_Intersect = 0;
	for (int i = 0; i < intersect.cols; i++) {
		for (int j = 0; j < intersect.rows; j++) {
			if (intersect.at<float>(i, j) > max_Intersect) {
				max_Intersect = intersect.at<float>(i, j);
			}
		}
	}

	return max_Intersect > intesect_threshold;
}

void detectAndDisplay(Mat img);
int main(int argc, char** argv) {
	Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!cascade.load(cascade_name)) { printf("--(!)Error loading\n"); return -1; };
	std::vector<Vec2f> lines;
	detectAndDisplay(img);

	imwrite("detected.jpg", img);

	return 0;



}

void detectAndDisplay(Mat img) {
	std::vector<Rect> darts;
	Mat frame_gray;
	Mat frame_lines;

	cvtColor(img, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	cvtColor(img,frame_lines, CV_BGR2GRAY);
	int centerPoint[100]; //for circle centers`
	cascade.detectMultiScale(frame_gray, darts, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500));
	for (int i = 0; i < darts.size(); i++) {
		int validate = 0;
		if (search_hough_line(frame_lines, darts[i])) {
			validate++;
		}
		//if something detect circle ,validate++
		if (validate == 2) {
			cv::rectangle(img, Point(darts[i].x, darts[i].y), Point(darts[i].x + darts[i].width, darts[i].y + darts[i].height), Scalar(0, 255, 0), 2);
		}
	}

	}

