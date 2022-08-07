//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <glm/glm.hpp>
#include <utility>

#include "hittable.h"


class Sphere : public Hittable {

public:
    Sphere(glm::vec3 center, float radius, std::shared_ptr<Material> material)
            : Hittable(std::move(material)),
              center_(center),
              radius_(radius) {

    }
    glm::vec3 center() const;
    float radius() const;
    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;


private:
    glm::vec3 center_;
    float radius_;

};


#endif //RAYTRACER_SPHERE_H
