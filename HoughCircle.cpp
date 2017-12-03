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

//void accumulator(int height, int width, Mat img);

int main() {
  int img_height;
  int img_width;

  Mat original_image;
  original_image = imread("dart7.jpg", 1);

  if(!original_image.data){
    return -1;
  }

  img_height = original_image.rows;
  img_width = original_image.cols;
  printf("%d, %d", img_width, img_height);

  Mat image_grey;
  cvtColor(original_image, image_grey, CV_BGR2GRAY);

  Mat image_grey_blur;
  GaussianBlur(image_grey, image_grey_blur, Size(9,9),0 ,0);

//  Mat image_edge;
//  Canny(image_grey_blur, image_edge, 80, 150, 3);

  vector<Vec3f> transformed_high_circle;
  vector<Vec3f> transformed_low_circle;


//  HoughCircles(image_grey_blur, transformed_circle, CV_HOUGH_GRADIENT, 1, image_grey_blur.rows/3, 100, 60, 0, min(img_width, img_height));
  HoughCircles(image_grey_blur, transformed_high_circle, CV_HOUGH_GRADIENT, 1, image_grey_blur.rows/10, 180, 75, 50, (min(img_width, img_height) / 2*3));
  HoughCircles(image_grey_blur, transformed_low_circle, CV_HOUGH_GRADIENT, 1, image_grey_blur.rows/10, 40, 30, 0, 300);


for( size_t i = 0; i < transformed_high_circle.size(); i++ )
{
  for (size_t z = 0; z < transformed_low_circle.size(); z++){
    Point center_high(cvRound(transformed_high_circle[i][0]), cvRound(transformed_high_circle[i][1]));
    Point center_low(cvRound(transformed_low_circle[i][0]), cvRound(transformed_low_circle[i][1]));
    if(cvRound (sqrt(pow((transformed_high_circle[i][0] - transformed_low_circle[i][0]), 2) + pow((transformed_high_circle[i][1] - transformed_low_circle[i][1]), 2))) < 50)
    {
      int radius_high = cvRound(transformed_high_circle[i][2]);
         int radius_low = cvRound(transformed_low_circle[i][2]);
         // circle center
     circle( original_image, center_high, 3, Scalar(0,255,0), -1, 8, 0 );
          circle( original_image, center_low, 3, Scalar(0,255,0), -1, 8, 0 );
         // circle outline
     circle( original_image, center_high, radius_high, Scalar(255,255,0), 3, 8, 0 );
          circle( original_image, center_low, radius_low, Scalar(255,255,0), 3, 8, 0 );
    }
  }
 }


/*
for( size_t i = 0; i < transformed_low_circle.size(); i++ )
{
   Point center(cvRound(transformed_low_circle[i][0]), cvRound(transformed_low_circle[i][1]));
   int radius = cvRound(transformed_low_circle[i][2]);
   // circle center
   circle( original_image, center, 3, Scalar(0,255,0), -1, 8, 0 );
   // circle outline
   circle( original_image, center, radius, Scalar(255,255,0), 3, 8, 0 );
 }




for( size_t i = 0; i < transformed_high_circle.size(); i++ )
{
   Point center(cvRound(transformed_high_circle[i][0]), cvRound(transformed_high_circle[i][1]));
   int radius = cvRound(transformed_high_circle[i][2]);
   // circle center
   circle( original_image, center, 3, Scalar(0,255,0), -1, 8, 0 );
   // circle outline
   circle( original_image, center, radius, Scalar(255,255,0), 3, 8, 0 );
 }
 */

 imshow( "Circle detected", original_image );

  waitKey(0);
  return 0;
}


/*
void accumulator(int height, int width, Mat img){
  double accum_x;
  double accum_y;
  double accum_degree;
  //image cross distance
  double diagonal_distance;

  int depth_of_degree;

  Mat original_img = img.data();

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

    //    }
      }
  }

}*/
