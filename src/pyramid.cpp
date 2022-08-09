//
// Created by trios on 8/9/22.
//

#include "pyramid.h"

#include <cmath>

bool Triangle::hit(const Ray &r, HitRecord &hr, float max_time) const {
    auto v2_v1 = v2_ - v1_;
    auto v3_v1 = v3_ - v1_;
    auto p_vec = glm::cross(r.direction(), v3_v1);
    float det = glm::dot(v2_v1, p_vec);
    if (det < EPSILON) return false;

    float inv_det = 1 / det;

    auto t_vec = r.origin() - v1_;
    auto u = glm::dot(t_vec, p_vec) * inv_det;
    if (u < EPSILON || u > 1) return false;

    auto q_vec = glm::cross(t_vec, v2_v1);
    auto v = glm::dot(r.direction(), q_vec) * inv_det;
    if (v < EPSILON || u + v > 1) return false;

    hr.time = glm::dot(v3_v1, q_vec) * inv_det;
    hr.point = r.at(hr.time);
    hr.set_face_normal(r, normal);
    return true;
}

bool Pyramid::hit(const Ray &r, HitRecord &hr, float max_time) const {

    bool hit_anything = false;
    auto closest_so_far = max_time;
    for (const auto &t: triangles) {
        if (t.hit(r, hr, closest_so_far)) {
            hit_anything = true;
            closest_so_far = hr.time;
            hr = hr;
        }
    }

    if (plane_.hit(r, hr, closest_so_far)) {
        hit_anything = true;
    }
    if (hit_anything) hr.material = material_;
    return hit_anything;

}

Pyramid::Pyramid(float x1, float z1, float x2, float z2, float k, float height, const std::shared_ptr<Material> &m)
        : Hittable(m), height_(height) {

    plane_ = XZRect(x1, z1, x2, z2, k, m);
    auto v1 = glm::vec3(x1, k, z1);
    auto v2 = glm::vec3(x1, k, z2);
    auto v3 = glm::vec3(x2, k, z1);
    auto v4 = glm::vec3(x2, k, z2);
    auto normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
    auto v5 = (float(0.25) * (v1 + v2 + v3 + v4)) + (normal * height);

    triangles.emplace_back(v1, v2, v5);
    triangles.emplace_back(v1, v3, v5);
    triangles.emplace_back(v4, v2, v5);
    triangles.emplace_back(v4, v3, v5);
}
