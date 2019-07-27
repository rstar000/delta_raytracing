#include "image.hpp"

#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

using std::uint8_t;

void save_rgb_image(const string &filename, const vector<RGBPixel> &data, size_t width, size_t height)
{
    vector<uint8_t> target(width*height*3);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            RGBPixel pix = data[y * width + x];
            for(size_t c = 0; c < 3; ++c) {
                uint8_t v = static_cast<uint>(255 * pix[c]);
                target[y * 3 * width + 3 * x + c] = v;
            }
        }
    }

    stbi_write_png(filename.c_str(), width, height, 3, target.data(), 0);
}

void save_rgba_image(const string &filename, const vector<RGBAPixel> &data, size_t width, size_t height)
{
    int num_channels = 4;
    vector<uint8_t> target(width*height*num_channels);
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            RGBAPixel pix = data[y * width + x];
            for(size_t c = 0; c < num_channels; ++c) {
                uint8_t v = static_cast<uint>(255 * pix[c]);
                target[(y * width + x) * num_channels + c] = v;
            }
        }
    }

    stbi_write_png(filename.c_str(), width, height, 4, target.data(), 0);
}

