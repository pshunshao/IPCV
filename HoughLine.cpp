#include "Hough.h"
const int intesect_threshold = 4;
bool search_hough_line(Mat frame, Rect dartR){
  Rect rect(dartR.x,dartR.y,dartR.width,dartR.height);
  Mat frame_gray;
  Mat edges;
  Mat img;
  std::vector<Vec4i> lines;
  Canny(frame_gray, img, 100, 200, 3);
  img(rect).copyTo(edges);
  Mat intersect = Mat(edges.cols,edges.rows,CV_32FC1,Scalar::all(0));
  HoughLines(edges, lines, 1, CV_PI / 180, 50, 0, 0);
  for(size_t k = 0; k< lines.size();k++){
    float rho = lines[k][0],theta = lines[k][1];
    Point p1,p2;
    p1.x = 0;
    p1.y = (rho - (p1.x - edges.cols/2)  * cos(theta)) / sin(theta) + edges.rows/2;
    p2.x = lines.size();
    p2.y = (rho - (p2.x - edges.cols/2) * cos(theta)) / sin(theta) + edges.rows/2;
    double m = -cos(theta)/sin(theta), c = rho /sin(theta);
    for(int i; i< intersect.cols;i++){
      for(int j; j<intersect.rows;j++){
        if(j == cvRound(m*i +rho/sin(theta))){
          intersect.at<float>(i,j)++;
        }
      }
    }

  }
  float max_Intersect = 0;
  for (int i = 0; i < intersect.cols; i++) {
	  for (int j = 0; j < intersect.rows;j++) {
		  if (intersect.at<float>(x, y) > max_Intersect) {
			  max_Intersect = intersect.at<float>(x, y);
		  }
	  }
  }

  return max_Intersect > intesect_threshold;
}
