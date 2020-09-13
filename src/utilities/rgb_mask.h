#include "types.h"

namespace RGBMask
{
    RGBColor popColorFor(cv::Mat &rgb);
    cv::Mat buildMask(cv::Mat &rgb, RGBColor &color, float window);
}