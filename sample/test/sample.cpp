#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main(int argc, const char* argv[])
{
  Mat mat = imread("lena.jpg", cv::IMREAD_COLOR);
  namedWindow("sample", cv::WINDOW_AUTOSIZE);
  imshow("sample", mat);
  waitKey(0);
  destroyAllWindows();

  return 0;
}
