//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_PYRAMID_H
#define RAYTRACER_PYRAMID_H

#include <utility>
#include <vector>

#include "rect.h"

class Triangle : public Hittable {
public:
    explicit Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) : v1_(v1), v2_(v2), v3_(v3) {
        normal = glm::normalize(glm::cross(v3_ - v1_, v3_ - v2_));
    }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;

private:
    glm::vec3 v1_, v2_, v3_;
    glm::vec3 normal{};
};

class Pyramid : public Hittable {
public:
    Pyramid(float x1, float z1, float x2, float z2, float k, float height, const std::shared_ptr<Material> &m);

    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;

private:
    XZRect plane_;
    float height_;
    std::vector<Triangle> triangles;

};


#endif //RAYTRACER_PYRAMID_H
