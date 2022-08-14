//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H


#include <vector>
#include <algorithm>

#include "common/base_hittable.h"

class BVHNode {
public:
    BVHNode(const std::vector<std::shared_ptr<BaseHittable>> &objs, int start_index, int end_index)
            : start_index_(start_index), end_index_(end_index), is_leaf(false) {

        axis_ = std::round(Utils::random(0, 2) - EPSILON);
        objs_ = objs;
        if (end_index_ - start_index_ <= 1) {
            bb_ = objs[start_index]->bounding_box();
            is_leaf = true;
            return;
        }

        std::sort(objs_.begin() + start_index_, objs_.end() + end_index_,
                  [&](const std::shared_ptr<BaseHittable> &a, const std::shared_ptr<BaseHittable> &b) {
                      return compare_boxes(a, b, axis_);
                  });
        int mid = start_index_ + (end_index_ - start_index_) / 2;
        left_ = std::make_shared<BVHNode>(objs_, start_index_, mid);
        right_ = std::make_shared<BVHNode>(objs_, mid, end_index_);

        auto lower = glm::min(left_->bounding_box().lower(), right_->bounding_box().lower());
        auto upper = glm::max(left_->bounding_box().upper(), right_->bounding_box().upper());
        bb_ = AABB(lower, upper);
    }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {
        if (!bb_.hit(r, max_time))
            return false;

        if (is_leaf) return false;

        bool hit_left = left_->hit(r, hr, max_time);
        bool hit_right = right_->hit(r, hr, hit_left ? hr.time : max_time);

        return hit_left | hit_right;
    }

    static inline bool
    compare_boxes(const std::shared_ptr<BaseHittable> &a, const std::shared_ptr<BaseHittable> &b, int axis) {
        return a->bounding_box().lower()[axis] < b->bounding_box().lower()[axis];
    }

    AABB bounding_box() { return bb_; }


private:
    std::vector<std::shared_ptr<BaseHittable>> objs_;
    std::shared_ptr<BVHNode> left_;
    std::shared_ptr<BVHNode> right_;
    bool is_leaf;
    int axis_;
    AABB bb_;
    int start_index_;
    int end_index_;
};


#endif //RAYTRACER_BVH_H
