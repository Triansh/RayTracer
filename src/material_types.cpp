//
// Created by trios on 8/7/22.
//

#include <glm/gtx/norm.hpp>

#include "material_types.h"
#include "utils.h"


bool Metal::scatter(const Ray &r_in,
                    const glm::vec3 &hit_point,
                    const glm::vec3 &hit_point_normal,
                    bool is_front_face,
                    Color &attenuation,
                    Ray &scattered) const {
    glm::vec3 reflected = reflect(r_in.direction(), hit_point_normal);
    scattered = Ray(hit_point, reflected + fuzz_ * utils.random_in_unit_sphere());
    attenuation = texture_->get_color(hit_point);
    return (glm::dot(scattered.direction(), hit_point_normal) > 0);
}

glm::vec3 Metal::emit(const glm::vec3 &hit_point,
                      const glm::vec3 &hit_point_normal,
                      bool is_front_face) const {
    return glm::vec3(0);
}

bool DiffusedLight::scatter(const Ray &r_in,
                            const glm::vec3 &hit_point,
                            const glm::vec3 &hit_point_normal,
                            bool is_front_face,
                            Color &attenuation,
                            Ray &scattered) const {
    return false;
}

glm::vec3 DiffusedLight::emit(const glm::vec3 &hit_point,
                              const glm::vec3 &hit_point_normal,
                              bool is_front_face) const {
    return is_front_face ? (texture_->get_color(hit_point) * intensity_) : glm::vec3(0);
}

bool Lambertian::scatter(const Ray &r_in,
                         const glm::vec3 &hit_point,
                         const glm::vec3 &hit_point_normal,
                         bool is_front_face,
                         Color &attenuation,
                         Ray &scattered) const {
    auto scatter_direction = hit_point_normal + utils.random_in_unit_sphere();

    // Catch degenerate scatter direction
    if (glm::all(glm::lessThan(glm::abs(scatter_direction), glm::vec3(EPSILON))))
        scatter_direction = hit_point_normal;

    scattered = Ray(hit_point, scatter_direction);
    auto cosine = glm::dot(hit_point_normal, scattered.direction());
    attenuation = texture_->get_color(hit_point) * (cosine < 0 ? 0 : (cosine / glm::pi<float>()));
    return true;

}

glm::vec3 Lambertian::emit(const glm::vec3 &hit_point,
                           const glm::vec3 &hit_point_normal,
                           bool is_front_face) const {
    return glm::vec3(0);
}

bool Transparent::scatter(const Ray &r_in,
                          const glm::vec3 &hit_point,
                          const glm::vec3 &hit_point_normal,
                          bool is_front_face,
                          Color &attenuation,
                          Ray &scattered) const {
    auto ratio = is_front_face ? refractive_index : (1 / refractive_index);
    auto cosine = std::min(glm::dot(-r_in.direction(), hit_point_normal), float(-1));
    auto sine = std::sqrt(1 - cosine * cosine);

    auto refraction_possible = !((1 < sine * ratio) | schlik_approx(ratio, cosine));
    auto dir = refraction_possible
               ? refract(r_in.direction(), hit_point_normal, ratio)
               : reflect(r_in.direction(), hit_point_normal);
    scattered = Ray(hit_point, dir);
    attenuation = glm::vec3(1);
    return true;
}

glm::vec3 Transparent::emit(const glm::vec3 &hit_point,
                            const glm::vec3 &hit_point_normal,
                            bool is_front_face) const {
    return glm::vec3(0);
}

bool Transparent::schlik_approx(float ratio, float cosine) const {
    auto ref_ratio = std::pow((1 - ratio) / (1 + ratio), 2);
    auto spec_coeff = ref_ratio + ((1 - ref_ratio) * std::pow(1 - cosine, 5));
    return spec_coeff > utils.random();
}
