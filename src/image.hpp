#pragma once

#include <vector>
#include <string>

#include <Eigen/Dense>

using uchar = unsigned char;

using RGBPixel = Eigen::Vector3f;
using RGBAPixel = Eigen::Vector4f;

using std::vector;
using std::string;

void save_rgb_image(const string &filename, const vector<RGBPixel> &data, size_t width, size_t height);
void save_rgba_image(const string &filename, const vector<RGBAPixel> &data, size_t width, size_t height);

template<typename PixelType>
class Image
{
protected:
    size_t width, height;
    std::vector<PixelType> values;
public:
    Image(size_t width, size_t height) :
        width(width), height(height)
    {
        values.resize(width * height);
    }

    Image(size_t width, size_t height, PixelType fill_value) :
        width(width), height(height)
    {
        values.resize(width * height);
        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                values(y,x) = fill_value;
            }
        }
    }

    Image(const Image &other) :
        width(other.width),
        height(other.height),
        values(other.values)
    { }

    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }

    PixelType& operator() (size_t y, size_t x)
    {
        return values[y * width + x];
    }

    PixelType operator() (size_t y, size_t x) const
    {
        return values[y * width + x];
    }

    void save(const std::string &filename) {}
};


template<>
inline void Image<RGBPixel>::save(const std::string &filename)
{
    save_rgb_image(filename, values, width, height);
}

template<>
inline void Image<RGBAPixel>::save(const std::string &filename)
{
    save_rgba_image(filename, values, width, height);
}

