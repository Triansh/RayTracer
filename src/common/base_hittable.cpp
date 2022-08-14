//
// Created by trios on 8/6/22.
//

#include "base_hittable.h"
//
//void HitList::add(const std::shared_ptr<Hittable> &h) {
//    bool is_emitter = std::static_pointer_cast<Light>(h->material()) != nullptr;
//    hittables[is_emitter].push_back(h);
//}

bool HitList::hit(const Ray &r, HitRecord &hr) const {
    auto hit_anything = false;
    auto closest_so_far = infinity;

    for (const auto &hittable: hittables) {
//        for (const auto &object: hittable) {
//        HitRecord temp_rec{};
        if (hittable->hit_by_ray(r, hr, closest_so_far)) {
            hit_anything = true;
            closest_so_far = hr.time;
//            hr = hr;
        }
    }
//    }
    return hit_anything;
}
