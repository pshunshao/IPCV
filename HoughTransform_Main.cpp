#include <stdio.h>
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>


using namespace cv;

void accumulator(int height, int width);

int main() {
  int img_height;
  int img_width;

  Mat original_image;
  original_image = imread("dart5.jpg", 1);

  img_height = original_image.rows;
  img_width = original_image.cols;

  Mat image_grey;
  cvtColor(original_image, image_grey, CV_BGR2GRAY);

  Mat image_grey_blur;
  blur(image_grey, image_grey_blur, Size(3,3));

  Mat image_edge;
  Canny(image_grey_blur, image_edge, 80, 150, 3);

  accumulator(img_height, img_width);

  imshow("Display", image_edge);

  waitKey(0);
  return 0;
}

void accumulator(int height, int width){
  double accum_height;
  double accum_width;
  double diagonal_distance;

  diagonal_distance = sqrt((height * height) + (width * width));
  accum_height = diagonal_distance * 2;
  accum_width = 180;

  cv::Mat accum(180, accum_height, CV_64FC1);


}
