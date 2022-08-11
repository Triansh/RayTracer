//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_PYRAMID_H
#define RAYTRACER_PYRAMID_H

#include <utility>
#include <vector>

#include "rect.h"

template<class T>
class Triangle : public Hittable<T, Triangle> {
public:
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, std::shared_ptr<Material<T>> m)
            : v1_(v1), v2_(v2), v3_(v3), material_(m) {
        normal = glm::normalize(glm::cross(v3_ - v1_, v3_ - v2_));
    }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {
        auto v2_v1 = v2_ - v1_;
        auto v3_v1 = v3_ - v1_;
        auto p_vec = glm::cross(r.direction(), v3_v1);
        float det = glm::dot(v2_v1, p_vec);
        if (std::fabs(det) < EPSILON) return false;

        float inv_det = 1 / det;

        auto t_vec = r.origin() - v1_;
        auto u = glm::dot(t_vec, p_vec) * inv_det;
        if (u < EPSILON || u > 1 + EPSILON) return false;

        auto q_vec = glm::cross(t_vec, v2_v1);
        auto v = glm::dot(r.direction(), q_vec) * inv_det;
        if (v < EPSILON || u + v > 1 + EPSILON) return false;

        auto time = glm::dot(v3_v1, q_vec) * inv_det;
        if (time < EPSILON or time > max_time) return false;

        hr.time = time;
        hr.point = r.at(time);
        hr.material = material_;
        hr.set_face_normal(r, normal);
        return true;
    }

    glm::vec3 get_random(const glm::vec3 &point) const { return {1, 0, 0}; }

    float get_probability(glm::vec3 dir, glm::vec3 point) const { return 0; }


private:
    std::shared_ptr<Material<T>> material_;
    glm::vec3 v1_, v2_, v3_;
    glm::vec3 normal{};

};

template<class T>
class Pyramid : public Hittable<T, Pyramid> {
public:
    Pyramid(float x1, float z1, float x2, float z2, float k, float height, const std::shared_ptr<Material<T>> &m)
            : height_(height), material_(m), plane_(std::make_unique<XZRect<T>>(x1, z1, x2, z2, k, m)) {

        auto v1 = glm::vec3(x1, k, z1);
        auto v2 = glm::vec3(x1, k, z2);
        auto v3 = glm::vec3(x2, k, z1);
        auto v4 = glm::vec3(x2, k, z2);
        auto normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        auto v5 = (float(0.25) * (v1 + v2 + v3 + v4)) + (normal * height_);

        triangles.emplace_back(std::make_unique<Triangle<T>>(v1, v2, v5, m));
        triangles.emplace_back(std::make_unique<Triangle<T>>(v1, v3, v5, m));
        triangles.emplace_back(std::make_unique<Triangle<T>>(v4, v2, v5, m));
        triangles.emplace_back(std::make_unique<Triangle<T>>(v4, v3, v5, m));
    }

    glm::vec3 get_random(const glm::vec3 &point) const { return {1, 0, 0}; }

    float get_probability(glm::vec3 dir, glm::vec3 point) const { return 0; }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {

        bool hit_anything = false;
        auto closest_so_far = max_time;
        for (const auto &t: triangles) {
            if (t->hit(r, hr, closest_so_far)) {
                hit_anything = true;
                closest_so_far = hr.time;
                hr = hr;
            }
        }

        if (plane_->hit(r, hr, closest_so_far)) {
            hit_anything = true;
        }
        if (hit_anything) hr.material = material_;
        return hit_anything;
    }

private:
    std::unique_ptr<XZRect<T>> plane_;
    float height_;
    std::vector<std::unique_ptr<Triangle<T>>> triangles;
    std::shared_ptr<Material<T>> material_;

};


#endif //RAYTRACER_PYRAMID_H
