//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_MATERIAL_TYPES_H
#define RAYTRACER_MATERIAL_TYPES_H


#include "material.h"

class Lambertian : public Material<Lambertian> {
public:
    Lambertian(std::shared_ptr<Texture> texture) : Material(std::move(texture), false) {}

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 bool is_front_face,
                 Color &attenuation,
                 Ray &scattered) const;

    glm::vec3 emit(const glm::vec3 &hit_point,
                   const glm::vec3 &hit_point_normal,
                   bool is_front_face) const;

};


class Metal : public Material<Metal> {
public:
    Metal(std::shared_ptr<Texture> texture, float fuzz) : Material(std::move(texture), true), fuzz_(fuzz) {}

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 bool is_front_face,
                 Color &attenuation,
                 Ray &scattered) const;

    glm::vec3 emit(const glm::vec3 &hit_point,
                   const glm::vec3 &hit_point_normal,
                   bool is_front_face) const;

private:
    float fuzz_{};
};

class Transparent : public Material<Transparent> {
public:
    explicit Transparent() : Material(nullptr, true) {}

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 bool is_front_face,
                 Color &attenuation,
                 Ray &scattered) const;

    glm::vec3 emit(const glm::vec3 &hit_point,
                   const glm::vec3 &hit_point_normal,
                   bool is_front_face) const;

private:
    static bool schlik_approx(float ratio, float cosine) ;

    float refractive_index = 1.5;

};

class DiffusedLight : public Material<DiffusedLight> {
public:
    DiffusedLight(std::shared_ptr<Texture> texture, float intensity)
            : Material(std::move(texture)), intensity_(intensity) {}

    bool scatter(const Ray &r_in,
                 const glm::vec3 &hit_point,
                 const glm::vec3 &hit_point_normal,
                 bool is_front_face,
                 Color &attenuation,
                 Ray &scattered) const;

    glm::vec3 emit(const glm::vec3 &hit_point,
                   const glm::vec3 &hit_point_normal,
                   bool is_front_face) const;

private:
    float intensity_;

};

#endif //RAYTRACER_MATERIAL_TYPES_H
