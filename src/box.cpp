//
// Created by trios on 8/9/22.
//

#include "box.h"

bool Box::hit(const Ray &r, HitRecord &hr, float max_time) const {
    bool hit_anything = false;
    auto closest_so_far = max_time;
    for (const auto &rect: rects) {
        if (rect->hit(r, hr, closest_so_far)) {
            hit_anything = true;
            closest_so_far = hr.time;
            hr = hr;
        }
    }
    if (hit_anything) hr.material = material_;
    return hit_anything;
}

Box::Box(glm::vec3 lower, glm::vec3 upper, std::shared_ptr<Material> m)
        : Hittable(std::move(m)), upper_(upper), lower_(lower) {

    float x1 = lower_.x, y1 = lower_.y, z1 = lower_.z;
    float x2 = upper_.x, y2 = upper_.y, z2 = upper_.z;
    rects.emplace_back(std::make_unique<XYRect>(x1, y1, x2, y2, z1, nullptr));
    rects.emplace_back(std::make_unique<XYRect>(x1, y1, x2, y2, z2, nullptr));
    rects.emplace_back(std::make_unique<XZRect>(x1, z1, x2, z2, y1, nullptr));
    rects.emplace_back(std::make_unique<XZRect>(x1, z1, x2, z2, y2, nullptr));
    rects.emplace_back(std::make_unique<YZRect>(y1, z1, y2, z2, x1, nullptr));
    rects.emplace_back(std::make_unique<YZRect>(y1, z1, y2, z2, x2, nullptr));

}
