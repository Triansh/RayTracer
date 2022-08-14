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
    auto is_hit = false;
    for (const auto &hittable: hittables) {
        if (hittable->hit_by_ray(r, hr, max_time)) {
            is_hit = true;
            max_time = hr.time;
        }
    }
    return is_hit;
}

void HitList::set_bounding_box(const std::vector<std::shared_ptr<BaseHittable>> &objs) {
    glm::vec3 lower(infinity);
    glm::vec3 upper(-infinity);
    for (const auto &t: objs) {
        lower = glm::min(lower, t->bounding_box().lower());
        upper = glm::max(upper, t->bounding_box().upper());
    }
    bb_ = AABB(lower, upper);
}

void HitList::set_bounding_box() {
    set_bounding_box(hittables);

}
