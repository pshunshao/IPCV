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

void accumulator(int height, int width, Mat original_img);

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

  accumulator(img_height, img_width, original_image);

  imshow("Display", image_edge);

  waitKey(0);
  return 0;
}

void accumulator(int height, int width, Mat original_img){
  double accum_height;
  double accum_width;
  double diagonal_distance;
  int depth_of_degree;

  //This is not the degree of an angle, but rather the segment of degree
  //If this is 45, then the angle for each segment will be 180 / 45
  //In this case it woule be 180 segment, thus 1 degree for each segment
  depth_of_degree = 180;

  diagonal_distance = sqrt((height * height) + (width * width));
  accum_height = diagonal_distance * 2;
  accum_width = depth_of_degree;

  Mat accum(180, accum_height, CV_64FC1);

  double original_center_x;
  double original_center_y;

  original_center_y = height/2;
  original_center_x = width/2;

  for (int y = 0; y < original_center_y; y++)
  {
      for(int x = 0; x < original_center_x; x++)
      {
        if(original_img.at<uchar>(x, y) > 200){
// r= xcos(theta) + ysin(theta)
          double distance =
        }
      }
  }
}
