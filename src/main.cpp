#include <stdio.h>
#include <opencv2/highgui.hpp>
#include "utilities/rgb_mask.h"

using namespace cv;

int main(int argc, char **argv)
{
    cv::Mat src;
    if (argc != 2 || !(src = cv::imread(argv[1], 1)).data)
        return -1;

    RGBColor popColor = RGBMask::popColorFor(src);
    cv::Mat mask = RGBMask::buildMask(src, popColor, 0.1f);
    printf("popular color: %d, %d, %d\n", popColor.x, popColor.y, popColor.z);
    namedWindow( "RGB mask", 1 );
    imshow( "RGB mask", mask );
    waitKey();

    return 0;
}