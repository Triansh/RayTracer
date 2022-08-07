//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <random>


class Utils {
public:
    static float random(float mini = 0.0, float maxi = 1.0) {
        static std::uniform_real_distribution<double> distribution(mini, maxi);
        static std::mt19937 generator;
        return distribution(generator);
    };

    static glm::vec3 random_vec3(float mini = 0.0, float maxi = 1.0) {
        return {random(mini, maxi), random(mini, maxi), random(mini, maxi)};
    }

};


#endif //RAYTRACER_UTILS_H
