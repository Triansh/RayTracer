//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "common/base_material.h"
#include "utils/utils.h"

template<class T>
class Material : public BaseMaterial {
public:
    Material() = default;

    explicit Material(std::shared_ptr<Texture> texture, bool specular = false)
            : BaseMaterial(std::move(texture), specular) {}

    bool scatter_ray(const Ray &r_in,
                     const glm::vec3 &hit_point,
                     const glm::vec3 &hit_point_normal,
                     bool is_front_face,
                     Color &attenuation,
                     Ray &scattered) const override {
        return static_cast<const T &>(*this).scatter(
                r_in, hit_point, hit_point_normal, is_front_face, attenuation, scattered);
    }

    glm::vec3 emittedValue(const glm::vec3 &hit_point,
                           const glm::vec3 &hit_point_normal,
                           bool is_front_face) const override {
        return static_cast<const T &>(*this).emit(hit_point, hit_point_normal, is_front_face);
    }
};


#endif //RAYTRACER_MATERIAL_H
