//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include "hittables/hittable.h"

class AABB {
public:
    AABB(glm::vec3 minimum, glm::vec3 maximum): maximum_(maximum), minimum_(minimum) {}
    bool hit(const Ray & r, float max_time) const;

private:
    glm::vec3 minimum_;
    glm::vec3 maximum_;
};


class BVH {
public:
    BVH(const std::vector<std::shared_ptr<BaseHittable>> &objs);

private:
    std::shared_ptr<BVH> left;
    std::shared_ptr<BVH> right;
    Axis axis;
};


#endif //RAYTRACER_BVH_H
