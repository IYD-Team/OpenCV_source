#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, const char* argv[])
{
    const int markers_x         = 3;   // x方向に配置するマーカー数
    const int markers_y         = 2;   // y方向に配置するマーカー数
    const int marker_length     = 100; // マーカーのサイズ
    const int marker_separation = 20;  // マーカー間の間隔

    // dictionary生成
    const cv::aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = cv::aruco::DICT_4X4_50;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionary_name);

    // GridBoardオブジェクト生成
    cv::Ptr<cv::aruco::GridBoard> grid_board = cv::aruco::GridBoard::create(markers_x, markers_y, 
        marker_length, marker_separation, dictionary);

    // ボード画像生成
    const int margins = 40;
    cv::Size img_size;
    img_size.width  = markers_x * (marker_length + marker_separation) - marker_separation + 2 * margins;
    img_size.height = markers_y * (marker_length + marker_separation) - marker_separation + 2 * margins;
    cv::Mat board_img;
    grid_board->draw(img_size, board_img, margins);

    // 生成したボード画像を表示
    cv::imshow("aruco grid board", board_img);
    cv::waitKey(0);

    return 0;
}