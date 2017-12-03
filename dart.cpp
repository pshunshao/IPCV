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


vector<Vec2f> detectLines(Mat img);

bool search_hough_line(Mat frame, Rect dartR) {
	Rect rect(dartR.x, dartR.y, dartR.width, dartR.height);
	// GaussianBlur(src, src, Size(3,3),2);
	Mat frame_gray;
	Mat edges;
	Mat img;
	std::vector<Vec2f> lines;
	Canny(frame, img, 100, 200, 3);
	img(rect).copyTo(edges);
	Mat intersect = Mat(edges.cols, edges.rows, CV_32SC1, Scalar::all(0));
	HoughLines(edges, lines, 1, CV_PI / 180, 50, 0, 0);
	for (size_t k = 0; k< lines.size(); k++) {
		float rho = lines[k][0], theta = lines[k][1];
		Point p1, p2;
		p1.x = 0;
		p1.y = (rho - (p1.x - edges.cols / 2)  * cos(theta)) / sin(theta) + edges.rows / 2;
		p2.x = lines.size();
		p2.y = (rho - (p2.x - edges.cols / 2) * cos(theta)) / sin(theta) + edges.rows / 2;
		//calculate hough space
		double m = -cos(theta) / sin(theta), c = rho / sin(theta);
		for (int i = 0; i< intersect.cols; i++) {
			for (int j = 0; j<intersect.rows; j++) {
				if (j == cvRound(m*i + (rho / sin(theta)))) {
					intersect.at<float>(i, j)++;
				}
			}
		}

	}
	float max_Intersect = 0;
	for (int i = 0; i < intersect.cols; i++) {
		for (int j = 0; j < intersect.rows; j++) {
			if (intersect.at<float>(i, j) > max_Intersect) {
				//the point with how many lines going through will be considered as a central point of interected lines
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

vector<Vec3f> detectCircle(Mat img) {
	Mat frame_gray;
	vector<Vec3f> circles;
	vector<Vec3f> transformed_high_circle;
	vector<Vec3f> transformed_low_circle;
	int img_height = img.rows;
	int img_width = img.cols;

	// vector<Vec3f> transformed_low_circle;
	cvtColor(img, frame_gray, CV_BGR2GRAY);
	// GaussianBlur(frame_gray, frame_gray, Size(9,9),0 ,0);

	// HoughCircles(frame_grey, transformed_high_circle, CV_HOUGH_GRADIENT, 1, 1, 180, 75, 0, (min(img_width, img_height) / 2*3));
	HoughCircles(frame_gray, circles, CV_HOUGH_GRADIENT, 1, img.rows / 3, 80, 30, 0, 100);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

		int radius = cvRound(circles[i][2]);
		// circle center
		circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(img, center, radius, Scalar(255, 255, 0), 3, 8, 0);
	}
	return circles;

}

void detectAndDisplay(Mat img) {
	std::vector<Rect> darts;
	Mat frame_gray;
	Mat frame_lines;
	std::vector<Rect> finalDart;
	std::vector<Vec3f> finalcircle;
	std::vector<Vec3f> circles = detectCircle(img);
	cvtColor(img, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	cvtColor(img, frame_lines, CV_BGR2GRAY);
	int centerPoint[100]; //for circle centers`
	cascade.detectMultiScale(frame_gray, darts, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500));
	 if(darts.size() >0){
	 		for(int x = 0; x < darts.size();x++){
	 			for(int y = 0; y<circles.size(); y++){
	 				int center_x = circles[y][0];
	 				int center_y = circles[y][1];
	 			if(center_x > darts[x].x && center_x < darts[x].x+ darts[x].width){
	 				if(center_y > darts[x].y &&center_y< darts[x].y+ darts[x].height){
						//update dart boards with circles
	 					finalDart.push_back(darts[x]);
	
	
	 			}
	 		}
	
	 	}
	 }
	 }
	for (int i = 0; i < darts.size(); i++) {
		if (search_hough_line(frame_lines, darts[i])) {
			//update dart boards with lines
			finalDart.push_back(darts[i]);
		}
	}

	for (int i = 0; i < finalDart.size(); i++) {

		cv::rectangle(img, Point(finalDart[i].x, finalDart[i].y), Point(finalDart[i].x + finalDart[i].width, finalDart[i].y + finalDart[i].height), Scalar(0, 255, 0), 2);

	}


}
