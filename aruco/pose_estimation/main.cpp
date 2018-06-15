#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//read data from "cv::Mat" format variable
static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs) 
{
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["camera_matrix"] >> camMatrix;
    fs["distortion_coefficients"] >> distCoeffs;

    return true;
}

int main(int argc, const char* argv[])
{
    char *settings = "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
    VideoCapture camera(settings); //内蔵インカメラが0で，USBで接続したカメラに1以降が割り当てられている

	if (!camera.isOpened()) {
	std::cout << "failed to open camera.";
	return -1;
	}

    Mat cameraMatrix, distCoeffs; 
	readCameraParameters("calibration.yml", cameraMatrix, distCoeffs);

	// dictionary生成
    const aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = aruco::DICT_6X6_250;
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(dictionary_name);

	while(camera.grab())
	{
		Mat image;
		camera >> image;

	    // マーカーの検出
	    std::vector<int> marker_ids;
	    std::vector< std::vector<Point2f> > marker_corners;
	    Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();
	    aruco::detectMarkers(image, dictionary, marker_corners, marker_ids, parameters);

	    // if at least one marker detected 
	    if (marker_ids.size() > 0) 
		{
			// 検出したマーカーの描画
			aruco::drawDetectedMarkers(image, marker_corners, marker_ids);

			//ポーズ推定
			vector< Vec3d > rvecs, tvecs; 
			aruco::estimatePoseSingleMarkers(marker_corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs); 

			// draw axis for each marker 
			for(int i=0; i<marker_ids.size(); i++) 
			{
				aruco::drawAxis(image, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1); 
			}
			// cout << rvecs[0] << "\t\n"; //debug
                        cout << tvecs[0] << "\t\n";
		}

	 	imshow("marker_detection", image);
	    
	    int key = waitKey(1);
	    if(key == 113)//qボタンが押されたとき
        {
            break;//whileループから抜ける．
        }
        else if(key == 115)//sが押されたとき
        {
            //フレーム画像を保存する．
            imwrite("img.png", image);
        }
	}

	destroyAllWindows();

    return 0;
}
