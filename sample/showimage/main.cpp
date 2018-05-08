#include <iostream>
#include <opencv2/core.hpp>    // coreモジュールのヘッダーをインクルード
#include <opencv2/highgui.hpp> // highguiモジュールのヘッダーをインクルード
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main()
{
    Mat img = imread("lena.jpg");
    imshow("image",img);
    waitKey(0);

    return 0;
}
