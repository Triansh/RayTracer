//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "common/base_hittable.h"

class BVHNode {
public:
    BVHNode(const std::vector<std::shared_ptr<BaseHittable>> &objs, int start_index, int end_index);

    bool hit(const Ray &r, HitRecord &hr, float max_time) const;

    static bool
    compare_boxes(const std::shared_ptr<BaseHittable> &a, const std::shared_ptr<BaseHittable> &b, int axis);

    AABB bounding_box() { return bb_; }


private:
    std::vector<std::shared_ptr<BaseHittable>> objs_;
    std::shared_ptr<BVHNode> left_;
    std::shared_ptr<BVHNode> right_;
    bool is_leaf;
    int axis_;
    AABB bb_{};
    int start_index_;
    int end_index_;

};


#endif //RAYTRACER_BVH_H
