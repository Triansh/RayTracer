//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include <vector>

#include "rect.h"

class Box : public Hittable {

public:
    Box(glm::vec3 lower, glm::vec3 upper, std::shared_ptr<Material> m);
    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;


private:
    glm::vec3 upper_;
    glm::vec3 lower_;
    std::vector<std::unique_ptr<Rect>> rects;
};


#endif //RAYTRACER_BOX_H
