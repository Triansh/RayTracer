//
// Created by trios on 8/6/22.
//

#include <glm/gtx/norm.hpp>

#include "sphere.h"
#include "utils.h"

bool Sphere::hit(const Ray &r, HitRecord &hr, float max_time) const {

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
    hr.material = material_;
    return true;
}

glm::vec3 Sphere::center() const {
    return center_;
}

float Sphere::radius() const {
    return radius_;
}
