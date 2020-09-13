#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "utilities/rgb_mask.h"

using namespace std;

int main(int argc, char **argv)
{
    cv::Mat src;
    if (argc != 2 || !(src = cv::imread(argv[1], 1)).data)
        return -1;

    printf("image size %d x %d\n", src.rows, src.cols);
    cout<<test();
    return 0;
}