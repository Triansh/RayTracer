//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include <vector>

#include "hittables/rect.h"

template<typename T>
class Box : public Hittable<T, Box> {

public:
    Box(glm::vec3 lower, glm::vec3 upper, std::shared_ptr<Material<T>> m)
            : upper_(upper), lower_(lower), material_(m) {

        float x1 = lower_.x, y1 = lower_.y, z1 = lower_.z;
        float x2 = upper_.x, y2 = upper_.y, z2 = upper_.z;
        rects.emplace_back(std::make_unique<XYRect<T>>(x1, y1, x2, y2, z1, nullptr));
        rects.emplace_back(std::make_unique<XYRect<T>>(x1, y1, x2, y2, z2, nullptr));
        rects.emplace_back(std::make_unique<XZRect<T>>(x1, z1, x2, z2, y1, nullptr));
        rects.emplace_back(std::make_unique<XZRect<T>>(x1, z1, x2, z2, y2, nullptr));
        rects.emplace_back(std::make_unique<YZRect<T>>(y1, z1, y2, z2, x1, nullptr));
        rects.emplace_back(std::make_unique<YZRect<T>>(y1, z1, y2, z2, x2, nullptr));

    }

    glm::vec3 get_random(const glm::vec3 &point) const { return {1, 0, 0}; }

    float get_probability(glm::vec3 dir, glm::vec3 point) const { return 0; }

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {
        bool hit_anything = false;
        auto closest_so_far = max_time;
        for (const auto &rect: rects) {
            if (rect->hit(r, hr, closest_so_far)) {
                hit_anything = true;
                closest_so_far = hr.time;
                hr = hr;
            }
        }
        if (hit_anything) hr.material = material_;
        return hit_anything;
    }


private:
    std::shared_ptr<Material<T>> material_;
    std::vector<std::unique_ptr<AxisAlignedRect<T>>> rects;
    glm::vec3 upper_;
    glm::vec3 lower_;

};


#endif //RAYTRACER_BOX_H
