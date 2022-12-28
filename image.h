#ifndef IMAGE_H
#define IMAGE_H

#include <stb_image_write.h>

#include <cstddef>
#include <vector>
#include <string>

#include "vec.h"

const int channels = 3;

struct image {
    std::vector<std::vector<color>> d;
    image(std::size_t h_, std::size_t w_);
    std::size_t h, w;
    color& operator()(std::size_t y, std::size_t x);
    color operator()(std::size_t y, std::size_t x) const;
    bool write_png(const std::string& filename) const;
};

#endif
