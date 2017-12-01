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

void accumulator(int height, int width, Mat& img);

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

  accumulator(img_height, img_width, image_edge);

  imshow("Display", image_edge);

  waitKey(0);
  return 0;
}

void accumulator(int height, int width, Mat& img){
  double accum_x;
  double accum_y;
  double accum_degree;
  //image cross distance
  double diagonal_distance;

  int depth_of_degree;

  Mat original_img = img.clone();

  //This is not the degree of an angle, but rather the segment of degree
  //If this is 45, then the angle for each segment will be 180 / 45
  //In this case it woule be 180 segment, thus 1 degree for each segment
  depth_of_degree = 360;

  diagonal_distance = sqrt((height * height) + (width * width));

  accum_x = width;
  accum_y = height;
  accum_degree = depth_of_degree;

  double accum[width][height][depth_of_degree];

  double original_center_x;
  double original_center_y;

//original_img.at<uchar>(1, 1) = 255;

  original_center_y = height/2;
  original_center_x = width/2;

  for (int y = 0; y < height; y++)
  {
      for(int x = 0; x < width; x++)
      {
    //    if(1){
          /*
          for(int radius = 0; radius < min(height, width); radius ++){
            for(int degree = 0; degree < depth_of_degree; degree ++){
              // r = xcos + ysin
              // x0 = x + rcos , y0 = y + rsin
              double center_x;
              double center_y;
              center_x = x + (radius * cos(degree));
              center_y = y + (radius * sin(degree));
              accum[(int)center_x][(int)center_y][radius]++;
            }
          }
          */
    //    }
      }
  }
}
