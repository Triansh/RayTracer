//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


#include "hittables/hittable.h"
#include "utils/utils.h"

template<typename T>
class Sphere : public Hittable<T, Sphere> {

public:
    Sphere(glm::vec3 center, float radius, std::shared_ptr<Material<T>> material, bool hollow = false)
            : material_(std::move(material)),
              center_(center),
              radius_(radius),
              hollow_(hollow) {
    }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {

        auto oc = r.origin() - center_;
        auto a = glm::length2(r.direction());
        auto b_half = glm::dot(oc, r.direction());
        auto c = glm::length2(oc) - (radius_ * radius_);

        auto D = (b_half * b_half) - (a * c);
        if (D < 0) return false;

        auto sqrtD = sqrt(D);
        auto root = float(-b_half - sqrtD) / a;
        if (root < EPSILON || root > max_time) {
            root = float(-b_half + sqrtD) / a;
            if (root < EPSILON || root > max_time)
                return false;
        }

        hr.time = root;
        hr.point = r.at(root);
        auto normal = glm::normalize(hr.point - center_);
        hr.set_face_normal(r, normal);
//        if (hollow_) {
//            hr.normal *= -1;
//            hr.front_face = !hr.front_face;
//        }
        hr.material = material_;
        return true;

    };

    glm::vec3 get_random(const glm::vec3 &point) const { return {1, 0, 0}; }

    float get_probability(glm::vec3 dir, glm::vec3 point) const { return 0; }

private:
    std::shared_ptr<Material<T>> material_;
    glm::vec3 center_;
    float radius_;
    bool hollow_;

};


#endif //RAYTRACER_SPHERE_H
