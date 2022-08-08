//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <memory>

#include "ray.h"
#include "utils.h"
#include "texture.h"

class Material {
public:
    Material(std::shared_ptr<Texture> texture) : texture_(std::move(texture)) {}

    virtual bool scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         Color &attenuation,
                         Ray &scattered) const = 0;

    virtual glm::vec3 emit(const glm::vec3 &point) const {
        return {0, 0, 0};
    }


protected:
    std::shared_ptr<Texture> texture_;
};


#endif //RAYTRACER_MATERIAL_H
