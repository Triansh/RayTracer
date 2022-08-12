//
// Created by trios on 8/12/22.
//

#include "bvh.h"

bool AABB::hit(const Ray &r, float max_time) const {
    for (int i = 0; i < 3; i++) {
        auto dir_i = r.direction()[i];
        auto pos_i = r.origin()[i];
        auto t1 = (minimum_[0] - pos_i) / dir_i;
        auto t2 = (maximum_[0] - pos_i) / dir_i;
        if (dir_i < EPSILON) std::swap(t1, t2);
        t1 = std::max(t1, float(0));
        t2 = std::min(t2, max_time);
        if (t1 <= t2) return false;
    }
    return true;
}
