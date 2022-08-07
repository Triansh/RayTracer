//
// Created by trios on 8/6/22.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <iostream>
#include <glm/glm.hpp>

class Ray {

public:
    Ray() = default;
    Ray(glm::vec3 ori, glm::vec3 dir) : ori_(ori), dir_(glm::normalize(dir)) {}
    glm::vec3 at(float time) const { return ori_ + time* dir_; };
    glm::vec3 origin() const { return ori_; };
    glm::vec3 direction() const { return dir_; };


private:
    glm::vec3 ori_;
    glm::vec3 dir_;

};


#endif //RAYTRACER_RAY_H
