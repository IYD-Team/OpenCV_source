#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

int main(void){
  char *settings = "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
  cv::VideoCapture camera(settings);

  if (!camera.isOpened()) {
    std::cout << "Failed to open Camera" << std::endl;
    return 1;
  }

  while(camera.grab()){
    cv::Mat image;
    camera.retrieve(image);
    cv::namedWindow("out", 1);
    cv::imshow("out", image);

    while (char(cv::waitKey(10)) != 27);
  }

  return 0;
}
