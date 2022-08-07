//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <glm/glm.hpp>
#include "ray.h"

struct Color {

    Color() = default;

    void clamp() {
        r = glm::clamp(r, float(0), float(1));
        g = glm::clamp(g, float(0), float(1));
        b = glm::clamp(b, float(0), float(1));
    }

    Color(float red, float green, float blue) : r(red), g(green), b(blue) {
        clamp();
    }

    explicit Color(glm::vec3 vec) : r(vec.x), g(vec.y), b(vec.z) { clamp(); }

    glm::vec3 getVec() const {
        return {r, g, b};
    }

    float r;
    float g;
    float b;
};


class Material {
public:
    explicit Material(Color c = Color(1, 0, 0)) : albedo_(c) {}

    virtual bool scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         Color &attenuation,
                         Ray &scattered) const = 0;

    Color color() const { return albedo_; };

protected:
    Color albedo_;

};


#endif //RAYTRACER_MATERIAL_H
