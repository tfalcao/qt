// CannyStill.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

    cv::Mat imgOriginal = cv::imread("..//data//lenna.png");

    if (imgOriginal.empty()) {
        std::cout << "error: image not read from file\n\n";
        _getch();
        return(0);
    }

    // convert to grayscale
    cv::Mat imgGrayscale;
    cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);

    // blur
    cv::Mat imgBlurred;
    cv::GaussianBlur(imgGrayscale,          // input image
                     imgBlurred,                         // output image
                     cv::Size(5, 5),                     // smoothing window width and height in pixels
                     1.5);                               // sigma value, determines how much the image will be blurred

    // canny
    cv::Mat imgCanny;
    cv::Canny(imgBlurred,           // input image
              imgCanny,                   // output image
              100,                        // low threshold
              200);                       // high threshold

    cv::namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);     // note: you can use CV_WINDOW_NORMAL which allows resizing the window
    cv::namedWindow("imgCanny", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image

    cv::imshow("imgOriginal", imgOriginal);     // show windows
    cv::imshow("imgCanny", imgCanny);

    cv::waitKey(0);                 // hold windows open until user presses a key

    return(0);
}
