//
// Created by trios on 8/11/22.
//

#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H

#include <hittable.h>
#include <memory>


class HittablePdf {
public:
    HittablePdf(std::shared_ptr<BaseHittable> h, const glm::vec3 &point) : ptr_(std::move(h)), point_(point) {}

    virtual float probability(const glm::vec3 &direction) const {
        return ptr_->probability( direction, point_);
    }

    virtual glm::vec3 random() const {
        return ptr_->random(point_);
    }

private:
    glm::vec3 point_;
    std::shared_ptr<BaseHittable> ptr_;
};


#endif //RAYTRACER_PDF_H
