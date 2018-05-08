#include <iostream>
#include <opencv2/core.hpp>    // coreモジュールのヘッダーをインクルード
#include <opencv2/highgui.hpp> // highguiモジュールのヘッダーをインクルード
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp> //cvtColor関数を使うための関数

using namespace cv;

int main()
{
    Mat img = imread("lena.jpg");
    Mat gray, dst;
    cvtColor(img, gray, CV_RGB2GRAY);
    threshold(gray, dst, 80, 200, 0);
    imshow("image",dst);
    waitKey(0);

    return 0;
}