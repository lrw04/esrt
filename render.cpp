#include "render.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <execution>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <random>
#include <vector>

#include "rng.h"

color pixel_color(std::shared_ptr<object> obj, const ray& r, unsigned depth) {
    if (!depth) return {};
    auto h = obj->intersect(r, {eps, INFINITY});
    if (!h.has_value()) return {};  // TODO: skybox?
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
    std::vector<std::size_t> scanlines;
    for (std::size_t y = 0; y < h; y++) scanlines.push_back(y);
    std::mt19937_64 rng(0);
    std::shuffle(scanlines.begin(), scanlines.end(), rng);

    std::atomic<std::size_t> finished = 0;
    std::mutex io;

    auto start = std::chrono::steady_clock::now();

    std::for_each(
        std::execution::par_unseq, scanlines.begin(), scanlines.end(),
        [&](std::size_t y) {
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
            finished++;
            io.lock();
            if (finished * 100 / h != (finished - 1) * 100 / h) {
                std::cerr << "\r" << finished << "/" << h << " scanlines ("
                          << finished * 100 / h << "%)";
            }
            io.unlock();
        });
    std::cerr << "\n";

    std::chrono::duration<double> elapsed =
        std::chrono::steady_clock::now() - start;
    std::cerr << "Done in " << elapsed.count() << " s." << std::endl;
    return im;
}
