//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include <glm/glm.hpp>

#include "material.h"

class Lambertian : public Material {
public:
    explicit Lambertian(Color c) : Material(c) {}
    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 Color &attenuation,
                 Ray &scattered) const override;
};


class Metal : public Material {
public:
    explicit Metal(Color c,float fuzz = 1) : Material(c), fuzz_(fuzz) {}
    static glm::vec3 reflect(glm::vec3 v, glm::vec3 n);
    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 Color &attenuation,
                 Ray &scattered) const override;
private:
    float fuzz_;
};

class DiffusedLight : public  Material {
public:
    DiffusedLight(Color c, float intensity) : Material(c), intensity_(intensity) {}
    bool scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         Color &attenuation,
                         Ray &scattered) const override;
    glm::vec3 emit(const glm::vec3 &point) const override;

private:
    float intensity_;

};
#endif //RAYTRACER_METAL_H
