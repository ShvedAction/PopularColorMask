#include "hsv_mask.h"

using namespace cv;

Mat HSVMask::buildMask(Mat &rgb, float window)
{
    Mat hsv;
    cvtColor(rgb, hsv, COLOR_BGR2HSV);

    float hranges[] = { 0, 180 };
    const float *ranges[] = { hranges };
    int histSize[] = { static_cast<int>(180.0f * (1.0f - window)) };
    int channels[] = { 0 };
    MatND hist;
    calcHist(&hsv, 1, channels, Mat(), // do not use mask
             hist, 1, histSize, ranges,
             true, // the histogram is uniform
             false);

    // find maximum
    double maxVal = 0;
    Point *maxLoc = new Point2i();
    minMaxLoc(hist, 0, &maxVal, 0, maxLoc);

    // convert argument of maximum to hue value
    uint8_t popHue = (*maxLoc).y / (1.0f - window);

    // extract hue channels
    std::vector<Mat> chan(3);
    cv::split(hsv, chan);

    // find diff with popular hue
    Mat mask(hsv.rows, hsv.cols, CV_16SC1, Scalar(0));
    Mat m1(hsv.rows, hsv.cols, CV_16SC1, Scalar(0));
    chan[0].convertTo(m1, CV_16SC1);
    absdiff(m1, popHue, mask);
    subtract(m1, 180, m1);
    absdiff(m1, popHue, m1);


    // There is problem with distance between two values of hue
    // Example hue1 = 10 and hue2 = 170, so distacne should be 20.
    // Cause 0 is red and 180 is red (in opencv 180 is last value of hue)
    min(m1, mask, mask);

    mask.convertTo(m1, CV_8UC1);
    threshold(m1, mask, 180 * window, 255, THRESH_BINARY_INV);
    
    return mask;
}