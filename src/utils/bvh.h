//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "common/base_hittable.h"

class BVHNode : public HitList {
public:
    BVHNode(const std::vector<std::shared_ptr<BaseHittable>> &objs, int start_index, int end_index);

    bool hit_by_ray(const Ray &r, HitRecord &hr, float max_time) const override;

    static bool
    compare_boxes(const std::shared_ptr<BaseHittable> &a, const std::shared_ptr<BaseHittable> &b, int axis);


private:
    std::shared_ptr<BaseHittable> left_;
    std::shared_ptr<BaseHittable> right_;

};


#endif //RAYTRACER_BVH_H
