#ifndef IMAGE_H
#define IMAGE_H

#include <stb_image_write.h>

#include <cstddef>
#include <vector>
#include <string>

#include "vec.h"

struct image {
    std::vector<std::vector<color>> d;
    image(std::size_t h, std::size_t w);
    color& operator()(std::size_t y, std::size_t x);
    color operator()(std::size_t y, std::size_t x) const;
    bool write_png(const std::string& filename) const;
};

#endif
