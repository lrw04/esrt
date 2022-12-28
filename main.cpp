#include "camera.h"
#include "image.h"
#include "rng.h"
#include "scene.h"

// TODO: build in-memory representation of object
// TODO: calculate colors properly
// TODO: monte-carlo

color pixel_color(std::shared_ptr<object> obj, const ray& r, unsigned depth) {
    if (!depth) return {};
    auto h = obj->intersect(r, {eps, INFINITY});
    if (!h.has_value()) return {};  // TODO: skybox
    // TODO
    return {};
}

image render(std::shared_ptr<object> obj, const camera& cam, std::size_t w,
             unsigned samples, unsigned max_depth, real gamma) {
    std::size_t h = (std::size_t)(w / cam.aspect_ratio);
    image im(h, w);
    for (std::size_t y = 0; y < h; y++) {
        for (std::size_t x = 0; x < w; x++) {
            im(y, x) = {};
            for (unsigned i = 0; i < samples; i++) {
                im(y, x) += pixel_color(
                    obj,
                    cam((y + uniform_real()) / h, (x + uniform_real()) / w),
                    max_depth);
            }
            for (int i = 0; i < dim; i++) {
                im(y, x)[i] = pow(im(y, x)[i] / samples, 1 / gamma);
            }
        }
    }
    return im;
}

int main() {
    const int imh = 100, imw = 100;
    image im(imh, imw);
    for (int y = 0; y < imh; y++) {
        for (int x = 0; x < imw; x++) {
            im(y, x) = {(real)y / imh, (real)x / imw, 0};
        }
    }
    im.write_png("image.png");
}
