//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <glm/glm.hpp>
#include <memory>

#include "ray.h"
#include "utils.h"

typedef glm::vec3 Color;

//struct Color : public glm::vec3 {
//
////    Color() = default;
////
////    void clamp() {
//////        r = glm::clamp(r, float(0), float(1));
//////        g = glm::clamp(g, float(0), float(1));
//////        b = glm::clamp(b, float(0), float(1));
////    }
//
//    Color() = default;
//    Color(float red, float green, float blue) : glm::vec3(red, green, blue) {}
//    explicit Color(glm::vec3 vec) : glm::vec3(vec) {}
//
////    glm::vec3 getVec() const {
////        return {r, g, b};
////    }
//
//    float r() { return x; };
//
//    float g() { return y; };
//
//    float b() { return z; };
//};


class Material {
public:
    Material(Color c, std::shared_ptr<Utils> utils) : albedo_(c), utils_(std::move(utils)) {}

    virtual bool scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         Color &attenuation,
                         Ray &scattered) const = 0;

    virtual glm::vec3 emit(const glm::vec3 &point) const {
        return {0, 0, 0};
    }

    Color color() const { return albedo_; };

protected:
    Color albedo_;
    std::shared_ptr<Utils> utils_;

};


#endif //RAYTRACER_MATERIAL_H
