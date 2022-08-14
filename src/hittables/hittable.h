//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>
#include <vector>

#include "common/base_hittable.h"
#include "common/ray.h"


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



//class Emitter : public Hittable, Light {
//    Emitter(std::shared_ptr<Material> material, float intensity): Hittable(material), Light(material)
//};

#endif //RAYTRACER_HITTABLE_H
