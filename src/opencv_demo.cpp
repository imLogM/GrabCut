/*
 * author: LogM
 * date: 2018-06-11
 * information: A demo shows how to use "grab cut" in opencv2, implemented in C++
 *              In order to compile, you need to change "OpenCV_DIR", "OpenCV_LIB_DIR", "OpenCV_INCLUDE_DIRS" in "CMakeList.txt".
 */

#include <iostream>
#include <cassert>
#include <opencv2/opencv.hpp>

// global params, recording bounding box coordinates
int g_x_leftup = 0;     // "g_" means global param
int g_y_leftup = 0;
int g_x_rightdown = 0;
int g_y_rightdown = 0;


void get_mouse_position(int event, int x, int y, int flags, void* param) {
    /* Mouse callback. Get bounding box's coordinates.
     */
    if (event == cv::EVENT_LBUTTONDOWN) {
        g_x_leftup = x;
        g_y_leftup = y;
    } else if (event == cv::EVENT_LBUTTONUP) {
        g_x_rightdown = x;
        g_y_rightdown = y;
        assert(g_y_rightdown > g_x_leftup && g_x_rightdown > g_x_leftup);
    }
}

int main() {
    // 1. read image file
    cv::Mat src = cv::imread("../../img/1.jpg");
    assert(!src.empty());
    if (src.cols > 800 || src.rows > 800) {
        cv::resize(src, src, cv::Size(0, 0), 0.5, 0.5); // resize for speed
    }

    // 2. set mouse callback
    cv::namedWindow("src");
    cv::setMouseCallback("src", get_mouse_position);

    // 3. show image for setting bounding box coordinates
    cv::Mat src_texted = src.clone();
    cv::putText(src_texted, "Draw boundingbox, then press any key", cv::Point(0, src.rows*4/5), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
    cv::imshow("src", src_texted);
    cv::waitKey();

    // 4. show bounding box
    cv::Mat src_bboxed = src.clone();
    cv::rectangle(src_bboxed, cv::Point(g_x_leftup, g_y_leftup), cv::Point(g_x_rightdown, g_y_rightdown), cv::Scalar(0, 255, 0), 3);
    cv::putText(src_bboxed, "Press any key to see result", cv::Point(0, src.rows*4/5), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255), 2);
    cv::imshow("src", src_bboxed);
    cv::waitKey();

    // 5. grab cut
    cv::Mat mask = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    cv::Mat bgModel = cv::Mat::zeros(1, 65, CV_64FC1);
    cv::Mat fgModel = cv::Mat::zeros(1, 65, CV_64FC1);

    cv::Rect rect = cv::Rect(g_x_leftup, g_y_leftup, g_x_rightdown, g_y_rightdown);
    cv::grabCut(src, mask, rect, bgModel, fgModel, 5, cv::GC_INIT_WITH_RECT);
    cv::Mat mask2 = (mask == 1) + (mask == 3);  // 0 = cv::GC_BGD, 1 = cv::GC_FGD, 2 = cv::PR_BGD, 3 = cv::GC_PR_FGD
    cv::Mat dest;
    src.copyTo(dest, mask2);

    // 6. show result
    cv::imshow("dest", dest);
    cv::waitKey();

    return 0;
}

