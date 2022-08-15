//
// Created by trios on 8/11/22.
//

#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H


#include "common/base_hittable.h"

class InverseSquareLightPdf {
public:
    InverseSquareLightPdf(std::shared_ptr<BaseHittable> h, const glm::vec3 &point, const glm::vec3 &normal)
            : ptr_(std::move(h)), point_(point) {}

    virtual float probability(const glm::vec3 &direction) const {
        return float(0.5) * ptr_->probability(direction, point_);
    }

    virtual glm::vec3 random() const {
        return ptr_->random(point_);
    }

private:
    glm::vec3 point_;
    std::shared_ptr<BaseHittable> ptr_;
};


#endif //RAYTRACER_PDF_H
