//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "ray.h"
#include "material.h"
#include "material_types.h"
#include "utils.h"


struct HitRecord {
    glm::vec3 point;
    glm::vec3 normal;
    float time;
    std::shared_ptr<BaseMaterial> material;
    bool front_face;

    inline void set_face_normal(const Ray &r, const glm::vec3 &outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class BaseHittable {
public:
    virtual bool hit_by_ray(const Ray &r, HitRecord &hr, float max_time) const = 0;
};

template<typename M, template<typename> class T>
class Hittable : public BaseHittable {
public:
    bool hit_by_ray(const Ray &r, HitRecord &hr, float max_time) const override {
        return static_cast<const T<M> &>(*this).hit(r, hr, max_time);
    }
};


struct HitList {
    // 0 -> non emitters (non-lights)
    // 1 -> emitters (lights)
    std::vector<std::shared_ptr<BaseHittable>> hittables;

    void add(const std::shared_ptr<BaseHittable>& h) { hittables.push_back(h); };

    bool hit(const Ray &r, HitRecord &hr) const;

};



//class Emitter : public Hittable, Light {
//    Emitter(std::shared_ptr<Material> material, float intensity): Hittable(material), Light(material)
//};

#endif //RAYTRACER_HITTABLE_H
