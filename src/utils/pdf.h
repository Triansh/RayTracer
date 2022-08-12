//
// Created by trios on 8/11/22.
//

#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H

#include "hittables/hittable.h"
#include <memory>


class HittablePdf {
public:
    HittablePdf(std::shared_ptr<BaseHittable> h, const glm::vec3 &point, const glm::vec3 &normal) : ptr_(std::move(h)),
                                                                                                    point_(point) {
//        w = glm::normalize(normal);
//        v = glm::normalize(glm::cross(w, glm::abs(w.x) > .9 ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0)));
//        u = glm::cross(w, v);
    }

    virtual float probability(const glm::vec3 &direction) const {
//        auto cosine_prob = float(0.5) * glm::dot(direction, point_);
        return float(0.5) * ptr_->probability(direction, point_);
//               + (cosine_prob <= 0 ? 0 : (cosine_prob / glm::pi<float>()));
    }

    virtual glm::vec3 random() const {
//        auto toss = utils.random();
//        if (toss < 0.5)
            return ptr_->random(point_);
//        auto random_cos = utils.random_cosine();
//        return u * random_cos.x + v * random_cos.y + w * random_cos.z;

    }

private:
    glm::vec3 point_;
    glm::vec3 u, v, w;
    std::shared_ptr<BaseHittable> ptr_;
};


#endif //RAYTRACER_PDF_H
