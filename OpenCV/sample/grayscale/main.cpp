#include <iostream>
#include <opencv2/core.hpp>    // coreモジュールのヘッダーをインクルード
#include <opencv2/highgui.hpp> // highguiモジュールのヘッダーをインクルード
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp> //cvtColor関数を使うための関数

using namespace cv;

int main()
{
    Mat img = imread("lena.jpg");
    Mat dst;
    cvtColor(img, dst, CV_RGB2GRAY);
    imshow("image",dst);
    waitKey(0);

    return 0;
}
