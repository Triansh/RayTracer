//
// Created by trios on 8/12/22.
//

#ifndef RAYTRACER_BASE_MATERIAL_H
#define RAYTRACER_BASE_MATERIAL_H

#include <memory>
#include <functional>
#include "glm/gtx/norm.hpp"

#include "ray.h"
#include "texture.h"

class BaseMaterial {
public:
    explicit BaseMaterial(std::shared_ptr<Texture> texture, bool specular = false)
            : texture_(std::move(texture)), specular_(specular) {}

    virtual bool scatter_ray(const Ray &r_in,
                             const glm::vec3 &hit_point,
                             const glm::vec3 &hit_point_normal,
                             bool is_front_face,
                             Color &attenuation,
                             Ray &scattered) const = 0;

    virtual glm::vec3 emittedValue(const glm::vec3 &hit_point,
                                   const glm::vec3 &hit_point_normal,
                                   bool is_front_face) const = 0;

    bool is_specular() const { return specular_; }

    static glm::vec3 reflect(const glm::vec3 v, const glm::vec3 n) {
        return v - (2 * glm::dot(v, n) * n);
    }

    static glm::vec3 refract(const glm::vec3 &incident, const glm::vec3 &normal, float ratio) {
        float cosine = std::min(glm::dot(-incident, normal), float(1.0));
        auto perp = ratio * (incident + cosine * normal);
        auto parallel = -std::sqrt(std::abs(float(1.0) - glm::length2(perp))) * normal;
        return perp + parallel;
    }

protected:
    std::shared_ptr<Texture> texture_;
    bool specular_;
};

#endif //RAYTRACER_BASE_MATERIAL_H
