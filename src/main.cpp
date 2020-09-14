#include <stdio.h>
#include "utilities/rgb_mask.h"
#include "utilities/hsv_mask.h"
#include <string>

using namespace cv;
using namespace std;
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
    string outPath = string("../out/")+to_string(window);
    imwrite(outPath+"_rgb_mask.png", mask);

    cv::Mat hsvMask = HSVMask::buildMask(src, window);
    imwrite(outPath+"_hsv_mask.png", hsvMask);
    return 0;
}