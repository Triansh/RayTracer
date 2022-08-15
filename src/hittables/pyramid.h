//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_PYRAMID_H
#define RAYTRACER_PYRAMID_H


#include "rect.h"
#include "triangle.h"

template<class T>
class Pyramid : public HitList {
public:
    Pyramid(float x1, float z1, float x2, float z2, float k, float height, const std::shared_ptr<Material<T>> &m) {

        auto v1 = glm::vec3(x1, k, z1);
        auto v2 = glm::vec3(x1, k, z2);
        auto v3 = glm::vec3(x2, k, z1);
        auto v4 = glm::vec3(x2, k, z2);
        auto normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        auto v5 = (float(0.25) * (v1 + v2 + v3 + v4)) + (normal * height);

        add(std::make_shared<Triangle<T>>(v1, v2, v5, m));
        add(std::make_shared<Triangle<T>>(v1, v3, v5, m));
        add(std::make_shared<Triangle<T>>(v4, v2, v5, m));
        add(std::make_shared<Triangle<T>>(v4, v3, v5, m));
        add(std::make_shared<XZRect<T>>(x1, z1, x2, z2, k, m));

        set_bounding_box();
    }
};


#endif //RAYTRACER_PYRAMID_H
