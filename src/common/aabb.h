//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H


#include "ray.h"

class AABB {
public:
    AABB() = default;

    AABB(glm::vec3 minimum, glm::vec3 maximum) {
        maximum_ = glm::max(minimum, maximum);
        minimum_ = glm::min(minimum, maximum);
    }

    bool hit(const Ray &r, float max_time) const {
        for (int i = 0; i < 3; i++) {
            auto dir_i = r.direction()[i];
            auto pos_i = r.origin()[i];
            auto t1 = (minimum_[i] - pos_i) / dir_i;
            auto t2 = (maximum_[i] - pos_i) / dir_i;
            if (dir_i < EPSILON) std::swap(t1, t2);
            t1 = std::max(t1, float(0));
            t2 = std::min(t2, max_time);
            if (t2 <= t1) return false;
        }
        return true;
    }

    glm::vec3 lower() { return minimum_; }

    glm::vec3 upper() { return maximum_; }

private:
    glm::vec3 minimum_;
    glm::vec3 maximum_;
};

#endif //RAYTRACER_AABB_H
