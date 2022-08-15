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
            auto y1 = (minimum_[i] - pos_i) / dir_i;
            auto y2 = (maximum_[i] - pos_i) / dir_i;
            auto t1 = std::max(float(0), std::min(y1, y2));
            auto t2 = std::min(max_time, std::max(y1, y2));
            if (t2 < t1) return false;
        }
        return true;
    }

    glm::vec3 lower() { return minimum_; }

    glm::vec3 upper() { return maximum_; }

private:
    glm::vec3 minimum_{};
    glm::vec3 maximum_{};
};

#endif //RAYTRACER_AABB_H
