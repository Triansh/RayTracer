//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_PYRAMID_H
#define RAYTRACER_PYRAMID_H


#include "rect.h"
#include "triangle.h"

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

        auto lower = plane_->bounding_box().lower();
        auto upper = plane_->bounding_box().upper();
        for (const auto &t: triangles) {
            lower = glm::min(lower, t->bounding_box().lower());
            upper = glm::min(upper, t->bounding_box().upper());
        }
        this->bb_ = AABB(lower, upper);
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
            }
        }

        if (plane_->hit(r, hr, closest_so_far)) {
            hit_anything = true;
        }
        return hit_anything;
    }

private:
    std::unique_ptr<XZRect<T>> plane_;
    float height_;
    std::vector<std::unique_ptr<Triangle<T>>> triangles;
    std::shared_ptr<Material<T>> material_;

};


#endif //RAYTRACER_PYRAMID_H
