#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
    cv::Mat image;
    cv::VideoCapture camera(0);
 
	if (!camera.isOpened()) {
		std::cout << "failed to open camera.";
		return -1;
	}

	while(1)
	{
		camera >> image;

	    if (image.empty())
	    {
	        std::cerr << "Failed to open image file." << std::endl;
	        return -1;
	    }

	    // dictionary生成
	    const cv::aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = cv::aruco::DICT_4X4_50;
	    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionary_name);

	    // マーカーの検出
	    std::vector<int> marker_ids;
	    std::vector< std::vector<cv::Point2f> > marker_corners;
	    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
	    cv::aruco::detectMarkers(image, dictionary, marker_corners, marker_ids, parameters);

	    // 検出したマーカーの描画
	    cv::aruco::drawDetectedMarkers(image, marker_corners, marker_ids);
	 	cv::imshow("marker_detection", image);
	    
	    int key = cv::waitKey(1);
	    if(key == 113)//qボタンが押されたとき
        {
            break;//whileループから抜ける．
        }
        else if(key == 115)//sが押されたとき
        {
            //フレーム画像を保存する．
            cv::imwrite("img.png", image);
        }
	}

	cv::destroyAllWindows();

    return 0;
}
