//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "common/ray.h"
#include "utils/utils.h"
#include "common/base_hittable.h"


template<typename M, template<typename> class T>
class Hittable : public BaseHittable {
public:
    bool hit_by_ray(const Ray &r, HitRecord &hr, float max_time) const override {
        return static_cast<const T<M> &>(*this).hit(r, hr, max_time);
    }

    float probability(glm::vec3 dir, glm::vec3 point) const override {
        return static_cast<const T<M> &>(*this).get_probability(dir, point);
    }

    glm::vec3 random(glm::vec3 point) const override {
        return static_cast<const T<M> &>(*this).get_random(point);
    }
};


struct HitList {
    // 0 -> non emitters (non-lights)
    // 1 -> emitters (lights)
    std::vector<std::shared_ptr<BaseHittable>> hittables;

    void add(const std::shared_ptr<BaseHittable> &h) { hittables.push_back(h); };

    bool hit(const Ray &r, HitRecord &hr) const;

};



//class Emitter : public Hittable, Light {
//    Emitter(std::shared_ptr<Material> material, float intensity): Hittable(material), Light(material)
//};

#endif //RAYTRACER_HITTABLE_H
