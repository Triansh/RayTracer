//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_BASE_HITTABLE_H
#define RAYTRACER_BASE_HITTABLE_H

#include "base_material.h"
#include "aabb.h"

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

    virtual float probability(glm::vec3 dir, glm::vec3 point) const = 0;

    virtual glm::vec3 random(glm::vec3 point) const = 0;

    AABB bounding_box() const { return bb_; }

protected:
    AABB bb_{};
};


struct HitList {
    std::vector<std::shared_ptr<BaseHittable>> hittables;

    void add(const std::shared_ptr<BaseHittable> &h) { hittables.push_back(h); };

    bool hit(const Ray &r, HitRecord &hr) const;
};

#endif //RAYTRACER_BASE_HITTABLE_H
