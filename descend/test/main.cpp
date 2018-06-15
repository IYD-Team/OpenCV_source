#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs){
  FileStorage fs(filename, FileStorage::READ);
  if (!fs.isOpened()){
    return false;
  fs["camera_matrix"] >> camMatrix;
  fs["distortion_coefficients"] >> distCoeffs;

  return true;
  }
}

int main(int argc, const char* argv[]){
  string settings = "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
  VideoCapture camera(settings);
  
  if (!camera.isOpened()){
    cout << "Failed to open Camera." << endl;
    return -1;
  }

  Mat cameraMatrix, distCoeffs;
  readCameraParameters("calibration.yml", cameraMatrix, distCoeffs);

  const aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = aruco::DICT_6X6_250;
  Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(dictionary_name);

  while (camera.grab()){
    Mat image;
    camera >> image;

    vector<int> marker_ids;
    vector< vector<Point2f> > marker_corners;
    Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();

    aruco::detectMarkers(image, dictionary, marker_corners, marker_ids, parameters);

    if (marker_ids.size() > 0){
      vector<Vec3d> rvecs, tvecs;
      aruco::estimatePoseSingleMarkers(marker_corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
    }
  }
}
