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
int main() {
  Mat original_image;
  original_image = imread("../Dart/dart0.jpg", 1);

  Mat image_grey;
  cvtColor(original_image, image_grey, CV_BGR2GRAY);

//  Mat image_grey_blur;
//  blur(image_grey, image_grey_blur, Size(5,5));

  return 0;
}
