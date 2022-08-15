//
// Created by trios on 8/9/22.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "rect.h"

template<typename T>
class Box : public HitList {

public:
    Box(glm::vec3 lower, glm::vec3 upper, std::shared_ptr<Material<T>> m)
            : material_(m) {
        float x1 = lower.x, y1 = lower.y, z1 = lower.z;
        float x2 = upper.x, y2 = upper.y, z2 = upper.z;
        add(std::make_shared<XYRect<T>>(x1, y1, x2, y2, z1, m));
        add(std::make_shared<XYRect<T>>(x1, y1, x2, y2, z2, m));
        add(std::make_shared<XZRect<T>>(x1, z1, x2, z2, y1, m));
        add(std::make_shared<XZRect<T>>(x1, z1, x2, z2, y2, m));
        add(std::make_shared<YZRect<T>>(y1, z1, y2, z2, x1, m));
        add(std::make_shared<YZRect<T>>(y1, z1, y2, z2, x2, m));

        set_bounding_box();
    }

private:
    std::shared_ptr<Material<T>> material_;
};


#endif //RAYTRACER_BOX_H
