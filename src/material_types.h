//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_MATERIAL_TYPES_H
#define RAYTRACER_MATERIAL_TYPES_H

#include <glm/glm.hpp>
#include <utility>

#include "material.h"

class Lambertian : public Material {
public:
    explicit Lambertian(std::shared_ptr<Texture> texture) : Material(std::move(texture)) {}

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 Color &attenuation,
                 Ray &scattered) const override;
};


class Metal : public Material {
public:
    Metal(std::shared_ptr<Texture> texture, float fuzz) : Material(std::move(texture)), fuzz_(fuzz) {}

    static glm::vec3 reflect(glm::vec3 v, glm::vec3 n);

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 Color &attenuation,
                 Ray &scattered) const override;

private:
    float fuzz_;
};

class DiffusedLight : public Material {
public:
    DiffusedLight(std::shared_ptr<Texture> texture, float intensity)
            : Material(std::move(texture)), intensity_(intensity) {}

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 Color &attenuation,
                 Ray &scattered) const override;

    glm::vec3 emit(const glm::vec3 &point) const override;

private:
    float intensity_;

};

#endif //RAYTRACER_MATERIAL_TYPES_H
