#include "camera.h"
#include "image.h"
#include "material.h"
#include "rng.h"
#include "scene.h"

// TODO: build in-memory representation of object
// TODO: monte-carlo

color pixel_color(std::shared_ptr<object> obj, const ray& r, unsigned depth) {
    if (!depth) return {};
    auto h = obj->intersect(r, {eps, INFINITY});
    if (!h.has_value()) return {};  // TODO: skybox
    auto sc = h.value().mat->scattered(r, h.value());
    if (!sc.has_value())
        return h.value().mat->emitted(h.value().u, h.value().v, h.value().p);
    return h.value().mat->emitted(h.value().u, h.value().v, h.value().p) +
           sc.value().attenuation * pixel_color(obj, sc.value().out, depth - 1);
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
    // TODO: interface
}
