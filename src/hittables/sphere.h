//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "hittable.h"

template<typename T>
class Sphere : public Hittable<T, Sphere> {

public:
    Sphere(glm::vec3 center, float radius, std::shared_ptr<Material<T>> material)
            : material_(std::move(material)),
              center_(center),
              radius_(radius) {
        this->bb_ = AABB(center_ - radius_ - EPSILON, center_ + radius_ + EPSILON);
    }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {

        auto dist_center = r.origin() - center_;
        auto a = glm::length2(r.direction());
        auto b_half = glm::dot(dist_center, r.direction());
        auto c = glm::length2(dist_center) - (radius_ * radius_);

        auto D = (b_half * b_half) - (a * c);
        if (D < 0) return false;

        auto sq_root_D = sqrt(D);
        auto time_val = float(-b_half - sq_root_D) / a;
        if (time_val < EPSILON or time_val > max_time) {
            time_val = float(-b_half + sq_root_D) / a;
            if (time_val < EPSILON or time_val > max_time)
                return false;
        }

        hr.time = time_val;
        hr.point = r.at(time_val);
        auto normal = (hr.point - center_) / radius_;
        hr.set_normal(r, normal);
        hr.material = material_;
        return true;

    };

    glm::vec3 get_random(const glm::vec3 &point) const { return {1, 0, 0}; }

    float get_probability(glm::vec3 dir, glm::vec3 point) const { return 0; }

private:
    std::shared_ptr<Material<T>> material_;
    glm::vec3 center_;
    float radius_;

};


#endif //RAYTRACER_SPHERE_H
