#include "rgb_mask.h"

using namespace cv;
using namespace std;

int encode(MatIterator_<ColorChenal> r)
{
    // encode rgb color to one value. To be the uniq key.
    return int(r[0]) * 256 * 256 + int(r[1]) * 256 + int(r[2]);
};

RGBColor decode(int key)
{
    return RGBColor{static_cast<ColorChenal>(key >> 16), static_cast<ColorChenal>(key >> 8), static_cast<ColorChenal>(key)};
};

// There is a max distance between in two color in rgb dimension.
const int MAX_COLOR_DISTANCE = 3*255*255;

struct Operator
{
    Mat *source;
    RGBColor &color;
    float window;
    Mat result;

    Operator(Mat &rgb, RGBColor &color, const float window) : source{&rgb}, color{color}, window{window}
    {
        result = Mat::zeros(rgb.rows, rgb.cols, CV_8UC1);
    }

    void operator()(RGBColor &p, const int *position) const
    {
        int index = position[0] * result.cols + position[1];

        // I can't use -/+ operator of the point here, because uchar could be overflow
        float colorDistance = (p.x - color.x) * (p.x - color.x) +
                                (p.y - color.y) * (p.y - color.y) +
                                (p.z - color.z) * (p.z - color.z);
        
        result.data[index] = colorDistance/MAX_COLOR_DISTANCE > window ? 0 : 255;
    }
};

RGBColor RGBMask::popColorFor(Mat &rgb)
{
    // calc counts colors
    map<int, int> counts;
    for (MatIterator_<ColorChenal> c = rgb.begin<ColorChenal>(); c != rgb.end<ColorChenal>(); c++)
        counts[encode(c)]++;

    // find the most popular color
    int max = counts.begin()->second, maxKey = counts.begin()->second;
    for (map<int, int>::iterator it = counts.begin(); it != counts.end(); it++)
    {
        if (max < it->second)
        {
            max = it->second;
            maxKey = it->first;
        }
    }

    return decode(maxKey);
};

Mat RGBMask::buildMask(Mat &rgb, RGBColor &color, const float window)
{
    Operator builder(rgb, color, window);
    rgb.forEach<RGBColor>(builder);
    return builder.result;
};
