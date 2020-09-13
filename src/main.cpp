#include <stdio.h>
#include "utilities/rgb_mask.h"
#include "utilities/hsv_mask.h"

using namespace cv;

/**
 * argv[0] - path to image
 * argv[1] - window value for tresholding (in float)
*/
int main(int argc, char **argv)
{
    cv::Mat src;
    if (argc != 3 || !(src = cv::imread(argv[1], 1)).data)
        return -1;

    float window = atof(argv[2]);

    RGBColor popColor = RGBMask::popColorFor(src);
    cv::Mat mask = RGBMask::buildMask(src, popColor, window);
    imwrite("out/rgb_mask.png", mask);

    cv::Mat hsvMask = HSVMask::buildMask(src, window);
    imwrite("out/hsv_mask.png", hsvMask);
    return 0;
}