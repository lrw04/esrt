#include "image.h"

#include <algorithm>
#include <cinttypes>

image::image(std::size_t h_, std::size_t w_) {
    h = h_;
    w = w_;
    d = std::vector<std::vector<color>>(h, std::vector<color>(w));
}

color& image::operator()(std::size_t y, std::size_t x) { return d[y][x]; }
color image::operator()(std::size_t y, std::size_t x) const { return d[y][x]; }

bool image::write_png(const std::string& filename) const {
    std::vector<uint8_t> data;
    data.reserve(channels * d.size() * d[0].size());
    for (std::size_t i = 0; i < d.size(); i++) {
        for (std::size_t j = 0; j < d[i].size(); j++) {
            for (int k = 0; k < channels; k++) {
                int intensity =
                    (int)(std::max(std::min(d[i][j][k], (real)1), (real)0) *
                          256);
                if (intensity == 256) intensity--;
                data.push_back((uint8_t)intensity);
            }
        }
    }
    return stbi_write_png(filename.c_str(), d[0].size(), d.size(), channels,
                          data.data(), 0);
}
