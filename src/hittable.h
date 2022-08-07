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

struct HitRecord {
    glm::vec3 point;
    glm::vec3 normal;
    float time;
    std::shared_ptr<Material> material;
    bool front_face;

    inline void set_face_normal(const Ray& r, const glm::vec3 & outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable {
public:
    explicit Hittable(std::shared_ptr<Material> material) : material_(std::move(material)) {}
    virtual bool hit(const Ray &r, HitRecord &hr, float max_time) const = 0;
    std::shared_ptr<Material> material() const;

protected:
    std::shared_ptr<Material> material_;
};


struct HitList {
    std::vector<std::shared_ptr<Hittable>> hittables;

    void add(const std::shared_ptr<Hittable> &h);
    bool hit(const Ray & r, HitRecord &hr) const;

};

#endif //RAYTRACER_HITTABLE_H
