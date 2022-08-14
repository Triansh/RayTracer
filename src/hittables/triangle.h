//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "hittable.h"

template<class T>
class Triangle : public Hittable<T, Triangle> {
public:
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, std::shared_ptr<Material<T>> m)
            : v1_(v1), v2_(v2), v3_(v3), material_(m) {
        normal = glm::normalize(glm::cross(v3_ - v1_, v3_ - v2_));
        auto low = glm::min(v1, glm::min(v2, v3));
        auto high = glm::max(v1, glm::max(v2, v3));
        this->bb_ = AABB(low, high);
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

#endif //RAYTRACER_TRIANGLE_H
