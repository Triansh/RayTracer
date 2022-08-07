//
// Created by trios on 8/7/22.
//

#include <glm/gtx/norm.hpp>

#include "metal.h"
#include "utils.h"

constexpr float EPSILON = 1e-6;

glm::vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Utils::random_vec3(-1, 1);
        if (glm::length2(p) >= 1) continue;
        return glm::normalize(p);
    }
}

bool Metal::scatter(const Ray &r_in,
                    const glm::vec3 &hit_point,
                    const glm::vec3 &hit_point_normal,
                    Color &attenuation,
                    Ray &scattered) const {
    glm::vec3 reflected = reflect(r_in.direction(), hit_point_normal);
    scattered = Ray(hit_point, reflected + fuzz_ * random_in_unit_sphere());
    attenuation = albedo_;
    return (glm::dot(scattered.direction(), hit_point_normal) > 0);
}

glm::vec3 Metal::reflect(const glm::vec3 v, const glm::vec3 n) {
    return v - (2 * glm::dot(v, n) * n);
}


bool Lambertian::scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         Color &attenuation,
                         Ray &scattered) const {
    auto scatter_direction = hit_point_normal + random_in_unit_sphere();

    // Catch degenerate scatter direction
    if (glm::all(glm::lessThan(glm::abs(scatter_direction), glm::vec3(EPSILON))))
        scatter_direction = hit_point_normal;

    scattered = Ray(hit_point, scatter_direction);
    attenuation = albedo_;
    return true;

}
