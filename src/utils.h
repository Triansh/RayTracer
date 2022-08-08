//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <random>
#include <functional>
#include <glm/glm.hpp>

constexpr float EPSILON = 1e-6;


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

//     glm::vec3 random_vec3(float mini = 0.0, float maxi = 1.0) {
//        return {random(mini, maxi), random(mini, maxi), random(mini, maxi)};
//    }

    glm::vec3 random_in_unit_sphere() {
        return glm::normalize(random_normal_vec());
    }

    double random_normal() { return normal_random(); }

    glm::vec3 random_normal_vec() { return {random_normal(), random_normal(), random_normal()}; }

private:
    std::function<float()> normal_random;
    std::function<float()> uniform_random;

};


#endif //RAYTRACER_UTILS_H
