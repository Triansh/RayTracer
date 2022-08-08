//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <glm/glm.hpp>

#include "ray.h"

constexpr int IMAGE_HEIGHT = 400;
//constexpr float ASPECT_RATIO =  16.0 / 9;
constexpr float ASPECT_RATIO =  1;
constexpr int IMAGE_WIDTH = int(ASPECT_RATIO * IMAGE_HEIGHT);


class Camera {
public:
    glm::vec3 look_at{};
    glm::vec3 up{};
    float fov{};
    float viewport_width{};
    float viewport_height{};

    Camera() = default;
    Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 vup, float view)
            : pos_(pos), look_at(look), up(vup), fov(view) {
        auto theta = glm::radians(fov);
        viewport_height = int(2 * glm::tan(theta / 2));
        viewport_width = int(ASPECT_RATIO * viewport_height);

        auto w = glm::normalize(pos_ - look_at);
        auto u = glm::normalize(glm::cross(up, w));
        auto v = glm::cross(w, u);

        horizontal_ = 10 * float(viewport_width) * u;
        vertical_ = 10 * float(viewport_height) * v;
        lower_left_corner_ = pos - horizontal_ / (float) 2
                             - vertical_ / (float) 2 - (float(10) * w);
    }


    Ray get_ray(float s, float t) const {
        return {pos_,
                lower_left_corner_ + s * vertical_ + t * horizontal_ - pos_};
    }

private:
    glm::vec3 pos_{};
    glm::vec3 horizontal_{};
    glm::vec3 vertical_{};
    glm::vec3 lower_left_corner_{};


};


#endif //RAYTRACER_CAMERA_H
