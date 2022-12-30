#include "vec.h"

#include <cmath>

v3 operator*(real lhs, const v3& rhs) {
    return {lhs * rhs[0], lhs * rhs[1], lhs * rhs[2]};
}
