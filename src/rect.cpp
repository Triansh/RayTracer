//
// Created by trios on 8/7/22.
//

#include "rect.h"
#include "utils.h"

bool XYRect::hit(const Ray &r, HitRecord &hr, float max_time) const {

    float t = (k_ - r.origin().z) / r.direction().z;
    if (t > max_time or t < EPSILON) return false;

    auto x = r.origin().x + t * r.direction().x;
    auto y = r.origin().y + t * r.direction().y;

    if (!(x1_ <= x and x <= x2_ and y1_ <= y and y <= y2_)) return false;

    hr.point = glm::vec3(x, y, k_);
    hr.time = t;
    hr.set_face_normal(r, glm::vec3(0, 0, 1));
    hr.material = material_;
    return true;
}

bool YZRect::hit(const Ray &r, HitRecord &hr, float max_time) const {

    float t = (k_ - r.origin().x) / r.direction().x;
    if (t > max_time or t < EPSILON) return false;

    auto y = r.origin().y + t * r.direction().y;
    auto z = r.origin().z + t * r.direction().z;

    if (!(z1_ <= z and z <= z2_ and y1_ <= y and y <= y2_)) return false;

    hr.point = glm::vec3(k_, y, z);
    hr.time = t;
    hr.set_face_normal(r, glm::vec3(1, 0, 0));
    hr.material = material_;
    return true;
}

bool XZRect::hit(const Ray &r, HitRecord &hr, float max_time) const {

    float t = (k_ - r.origin().y) / r.direction().y;
    if (t > max_time or t < EPSILON) return false;

    auto x = r.origin().x + t * r.direction().x;
    auto z = r.origin().z + t * r.direction().z;

    if (!(x1_ <= x and x <= x2_ and z1_ <= z and z <= z2_)) return false;

    hr.point = glm::vec3(x, k_, z);
    hr.time = t;
    hr.set_face_normal(r, glm::vec3(0, 1, 0));
    hr.material = material_;
    return true;
}