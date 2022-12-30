#ifndef RENDER_H
#define RENDER_H

#include <memory>

#include "image.h"
#include "ray.h"
#include "scene.h"
#include "vec.h"
#include "camera.h"

color pixel_color(std::shared_ptr<object> obj, const ray& r, unsigned depth);

image render(std::shared_ptr<object> obj, const camera& cam, std::size_t w,
             unsigned samples, unsigned max_depth, real gamma);

#endif
