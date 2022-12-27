#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec.h"

struct camera {
    point o;
    v3 up, dir, luc, dify, difx;
    real aspect_ratio, fov;  // fov is horizontal
    camera(point o, v3 up, v3 dir, real aspect_ratio, real fov);
    ray operator()(real y, real x) const;
};

#endif
