#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> //cvtColor関数を使うための関数
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
	VideoCapture camera(0);

	// デバッグウインドウを開く
	namedWindow("debugwindow", CV_WINDOW_AUTOSIZE);

	int horizonalCrossCount = 10;
	int verticalCrossCount = 7;

	int image_width, image_height;

	// calibrate points
	vector<vector<Point3f> > object_points;
	vector<vector<Point2f> > image_points;
	vector<Point3f> obj;
	for(int j=0;j< horizonalCrossCount * verticalCrossCount;j++) {
	    obj.push_back(Point3f(j/horizonalCrossCount, j%horizonalCrossCount, 0.0f));
	}

	unsigned int numberOfImages = 1;
	for(unsigned int i=0; i<numberOfImages; i++) {
	    
	    char filename[32];
	    sprintf(filename, "../debugimage%d.png", i);
	    Mat frame = imread(filename);
	    image_width = frame.cols;
	    image_height = frame.rows;
	    Mat gray;
	    
	    flip(frame, frame, -1);
	    cvtColor(frame, gray, CV_BGR2GRAY);
	    
	    // 10-7 チェスを探す
	    Size chessboardPatterns(horizonalCrossCount, verticalCrossCount);
	    vector<Point2f> centers;
	    bool found = findChessboardCorners(gray, chessboardPatterns, centers, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
	    if (found) {
	        // 見つけたpointを高精度化する
	        cornerSubPix(gray, centers, Size(11,11), Size(-1,-1), TermCriteria (TermCriteria::EPS+TermCriteria::COUNT, 30, 0.1));
	        object_points.push_back(obj);
	        image_points.push_back(centers);
	        
	        // draw
	        drawChessboardCorners(gray, chessboardPatterns, Mat(centers), true);
	        imshow("debugWindow", gray);
	    } else {
	        cout << "not found" << endl;
	    }
	    
	    int key = waitKey(1);
	    if (key == 'q') {
	        break;
	    }
	}

	// calibrate
	vector<Mat> rvecs, tvecs;
	Mat mtx(3,3, CV_64F);
	Mat dist(8,1, CV_64F);
	calibrateCamera(object_points, image_points, Size(image_width, image_height), mtx, dist, rvecs, tvecs);

	//output yml file
	FileStorage fs("../calibration.yml", FileStorage::WRITE);
    fs << "camera_matrix" << mtx;
    fs << "distortion_coefficients" << dist;
    fs.release();

	unsigned int i=0;
	while(1) {
	    Mat frame;
	    camera >> frame;
	    flip(frame, frame, -1);
	    
	    if (++i > 10) {
	        Mat undistorted;
	        undistort(frame, undistorted, mtx, dist);
	        imshow("debugWindow", undistorted);
	        if (i==20) {
	            i=0;
	        }
	    } else {
	        imshow("debugWindow", frame);
	    }
	    
	    int key = waitKey(1);
	    if (key == 'q') {
	        break;
	    }
	}
}