//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <random>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

constexpr float EPSILON = 1e-6;
extern float infinity;

enum Axis {
    X, Y, Z
};

static int get_axis_num(Axis axis) {
    int ax = -1;
    if (axis == X) ax = 0;
    else if (axis == Y) ax = 1;
    else if (axis == Z) ax = 2;
    return ax;
}

class Utils {
public:

    Utils() {
        const static std::normal_distribution<float> normal_distribution(0, 1);
        const static std::mt19937 normal_generator;
        normal_random = std::bind(normal_distribution, normal_generator);

        const static std::uniform_real_distribution<float> uniform_distribution(0, 1);
        const static std::mt19937 uniform_generator;
        uniform_random = std::bind(uniform_distribution, uniform_generator);
    }

    float random() { return uniform_random(); };

    static float random(float min, float max) {
        return min + (float(max - min) * rand() / (RAND_MAX + 1.0));
    }

    static glm::vec3 random_vec3(float mini = 0.0, float maxi = 1.0) {
        return {random(mini, maxi), random(mini, maxi), random(mini, maxi)};
    }

    glm::vec3 random_cosine() {
        auto v1 = random();
        auto v2 = random();
        auto root_v2 = sqrt(v2);
        auto angle = 2 * glm::pi<float>() * v1;
        return {
                glm::cos(angle) * root_v2,
                glm::sin(angle) * root_v2,
                std::sqrt(1 - v2)
        };
    }

    glm::vec3 random_in_unit_sphere() {
        return glm::normalize(random_normal_vec());
    }

    double random_normal() { return normal_random(); }

    glm::vec3 random_normal_vec() { return {random_normal(), random_normal(), random_normal()}; }

private:
    std::function<float()> normal_random;
    std::function<float()> uniform_random;

};

extern Utils utils;

#endif //RAYTRACER_UTILS_H
