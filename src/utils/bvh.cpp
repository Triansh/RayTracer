//
// Created by trios on 8/12/22.
//

#include "bvh.h"

bool
BVHNode::compare_boxes(const std::shared_ptr<BaseHittable> &a, const std::shared_ptr<BaseHittable> &b, int axis) {
    return a->bounding_box().lower()[axis] < b->bounding_box().lower()[axis];
}

bool BVHNode::hit_by_ray(const Ray &r, HitRecord &hr, float max_time) const {
    if (!bb_.hit(r, max_time)) {
        return false;
    }
    bool hit_left = left_->hit_by_ray(r, hr, max_time);
    bool hit_right = right_->hit_by_ray(r, hr, hit_left ? hr.time : max_time);

    return hit_left | hit_right;
}

BVHNode::BVHNode(const std::vector<std::shared_ptr<BaseHittable>> &objs, int start_index, int end_index) {

    int axis = std::round(Utils::random(0, 2) - EPSILON);
    hittables = objs;
    if (end_index - start_index <= 1) {
        left_ = right_ = hittables[start_index];
    } else {
        std::sort(hittables.begin() + start_index, hittables.begin() + end_index,
                  [axis](const std::shared_ptr<BaseHittable> &a, const std::shared_ptr<BaseHittable> &b) {
                      return compare_boxes(a, b, axis);
                  });

        if (end_index - start_index <= 2) {
            left_ = hittables[start_index];
            right_ = hittables[start_index + 1];
        } else {
            int mid = start_index + (end_index - start_index) / 2;
            left_ = std::make_shared<BVHNode>(hittables, start_index, mid);
            right_ = std::make_shared<BVHNode>(hittables, mid, end_index);
        }
    }
    set_bounding_box({hittables.begin() + start_index, hittables.begin() + end_index});
}