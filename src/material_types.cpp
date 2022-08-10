//
// Created by trios on 8/7/22.
//

#include <glm/gtx/norm.hpp>

#include "material_types.h"
#include "utils.h"


bool Metal::scatter(const Ray &r_in,
                    const glm::vec3 &hit_point,
                    const glm::vec3 &hit_point_normal,
                    Color &attenuation,
                    Ray &scattered) const {
    glm::vec3 reflected = reflect(r_in.direction(), hit_point_normal);
    scattered = Ray(hit_point, reflected + fuzz_ * utils.random_in_unit_sphere());
    attenuation = texture_->get_color(hit_point);
    return (glm::dot(scattered.direction(), hit_point_normal) > 0);
}

glm::vec3 Metal::emit(const glm::vec3 &point) const {
    return glm::vec3(0);
}

glm::vec3 Metal::reflect(const glm::vec3 v, const glm::vec3 n) {
    return v - (2 * glm::dot(v, n) * n);
}


bool DiffusedLight::scatter(const Ray &r_in,
                            const glm::vec3 &hit_point,
                            const glm::vec3 &hit_point_normal,
                            Color &attenuation,
                            Ray &scattered) const {
    return false;
}

glm::vec3 DiffusedLight::emit(const glm::vec3 &point) const {
    return texture_->get_color(point) * intensity_;
}

bool Lambertian::scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         Color &attenuation,
                         Ray &scattered) const {
    auto scatter_direction = hit_point_normal + utils.random_in_unit_sphere();

    // Catch degenerate scatter direction
    if (glm::all(glm::lessThan(glm::abs(scatter_direction), glm::vec3(EPSILON))))
        scatter_direction = hit_point_normal;

    scattered = Ray(hit_point, scatter_direction);
    attenuation = texture_->get_color(hit_point);
    return true;

}

glm::vec3 Lambertian::emit(const glm::vec3 &point) const {
    return glm::vec3(0);
}


