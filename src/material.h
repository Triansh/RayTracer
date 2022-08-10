//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <memory>
#include <functional>

#include "ray.h"
#include "utils.h"
#include "texture.h"

class BaseMaterial {
public:
    explicit BaseMaterial(std::shared_ptr<Texture> texture) : texture_(std::move(texture)) {}

    virtual bool scatter_ray(const Ray &r_in,
                             const glm::vec3 &hit_point,
                             const glm::vec3 &hit_point_normal,
                             Color &attenuation,
                             Ray &scattered) const = 0;

    virtual glm::vec3 emittedValue(const glm::vec3 &point) const = 0;

protected:
    std::shared_ptr<Texture> texture_;
};

template<class T>
class Material : public BaseMaterial {
public:
    Material() = default;

    explicit Material(std::shared_ptr<Texture> texture) : BaseMaterial(std::move(texture)) {}

    bool scatter_ray(const Ray &r_in,
                     const glm::vec3 &hit_point,
                     const glm::vec3 &hit_point_normal,
                     Color &attenuation,
                     Ray &scattered) const override {
        return static_cast<const T &>(*this).scatter(
                r_in, hit_point, hit_point_normal, attenuation, scattered);
    }

    glm::vec3 emittedValue(const glm::vec3 &point) const override {
        return static_cast<const T &>(*this).emit(point);
    }
};


#endif //RAYTRACER_MATERIAL_H
