//
// Created by trios on 8/6/22.
//

#include "hittable.h"

std::shared_ptr<Material> Hittable::material() const {
    return material_;
}

void HitList::add(const std::shared_ptr<Hittable> &h) {
    hittables.push_back(h);
}

bool HitList::hit(const Ray &r, HitRecord &hr) const {
    auto hit_anything = false;
    auto closest_so_far = float(LONG_LONG_MAX);

    for (const auto &object: hittables) {
        HitRecord temp_rec{};
        if (object->hit(r, temp_rec, closest_so_far)) {
            hit_anything = true;
            closest_so_far = temp_rec.time;
            hr = temp_rec;
        }
    }
    return hit_anything;
}
