//
// Created by trios on 8/6/22.
//

#include "base_hittable.h"
//
//void HitList::add(const std::shared_ptr<Hittable> &h) {
//    bool is_emitter = std::static_pointer_cast<Light>(h->material()) != nullptr;
//    hittables[is_emitter].push_back(h);
//}

bool HitList::hit_by_ray(const Ray &r, HitRecord &hr, float max_time) const {
    auto hit_anything = false;
    for (const auto &hittable: hittables) {
        if (hittable->hit_by_ray(r, hr, max_time)) {
            hit_anything = true;
            max_time = hr.time;
        }
    }
    return hit_anything;
}
