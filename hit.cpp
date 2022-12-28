#include "hit.h"

std::optional<hit> operator^(const std::optional<hit>& a,
                             const std::optional<hit>& b) {
    if ((!a.has_value()) && (!b.has_value())) return std::nullopt;
    if (!a.has_value()) return b;
    if (!b.has_value()) return a;
    return a.value().t < b.value().t ? a : b;
}
