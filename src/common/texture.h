//
// Created by trios on 8/8/22.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H

#include <memory>

#include <glm/glm.hpp>

#include "utils/utils.h"


typedef glm::vec3 Color;

class Texture {
public:
    virtual Color get_color(const glm::vec3 &hit_point) const = 0;
};

class Solid : public Texture {
public:
    explicit Solid(Color color) : color_(color) {}

    Color get_color(const glm::vec3 &hit_point) const override {
        return color_;
    }

private:
    Color color_;
};

class CheckerBoard : public Texture {
public:
    CheckerBoard(std::shared_ptr<Texture> m1, std::shared_ptr<Texture> m2, float magnitude)
            : m1_(std::move(m1)), m2_(std::move(m2)), magnitude_(magnitude) {}

    Color get_color(const glm::vec3 &hit_point) const override {
        auto sign_vec = glm::sign(glm::cos(magnitude_ * hit_point));
//        std::cerr << sign_vec.x << " " << sign_vec.y << " " << sign_vec.z << " ";
        auto sign = sign_vec.x * sign_vec.y * sign_vec.z;
//        std::cerr << std::setprecision(10) << sign << '\n';
        return sign > EPSILON ? m1_->get_color(hit_point) : m2_->get_color(hit_point);
    };
private:
    std::shared_ptr<Texture> m1_;
    std::shared_ptr<Texture> m2_;
    float magnitude_;

};

#endif //RAYTRACER_TEXTURE_H
