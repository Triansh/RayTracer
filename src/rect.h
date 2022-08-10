//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_RECT_H
#define RAYTRACER_RECT_H

#include <utility>

#include "hittable.h"

enum Axis {
    X, Y, Z
};

template<class T>
class AxisAlignedRect : public Hittable<T, AxisAlignedRect> {

public:
    AxisAlignedRect() : material_(nullptr) {}

    AxisAlignedRect(float x1, float y1, float x2, float y2, float k, Axis ax, std::shared_ptr<Material<T>> m)
            : material_(m), x1_(x1), x2_(x2), y1_(y1), y2_(y2), k_(k), axis(ax) {}

    bool hit(const Ray &r, HitRecord &hr, float max_time) const {

        int ax;
        if (axis == X) ax = 0;
        else if (axis == Y) ax = 1;
        else if (axis == Z) ax = 2;

        float t = (k_ - r.origin()[ax]) / r.direction()[ax];
        if (t > max_time or t < EPSILON) return false;

        auto hit_point = r.origin() + t * r.direction();

        if (axis == X) {
            if (!(x1_ <= hit_point.y and hit_point.y <= x2_ and y1_ <= hit_point.z and hit_point.z <= y2_))
                return false;
            hr.set_face_normal(r, glm::vec3(0, 0, 1));
        } else if (axis == Y) {
            if (!(x1_ <= hit_point.x and hit_point.x <= x2_ and y1_ <= hit_point.z and hit_point.z <= y2_))
                return false;
            hr.set_face_normal(r, glm::vec3(0, 0, 1));
        } else if (axis == Z) {
            if (!(x1_ <= hit_point.x and hit_point.x <= x2_ and y1_ <= hit_point.y and hit_point.y <= y2_))
                return false;
            hr.set_face_normal(r, glm::vec3(0, 0, 1));
        }

        hr.point = hit_point;
        hr.time = t;
        hr.material = material_;
        return true;
    }

protected:
    std::shared_ptr<Material<T>> material_;
    float x1_{}, y1_{};
    float x2_{}, y2_{};
    float k_{};
    Axis axis;
};

template<class T>
class XYRect : public AxisAlignedRect<T> {
public:
    XYRect() = default;

    XYRect(float x1, float y1, float x2, float y2, float k, std::shared_ptr<Material<T>> m)
            : AxisAlignedRect<T>(x1, y1, x2, y2, k, Z, std::move(m)) {}
};


template<class T>
class YZRect : public AxisAlignedRect<T> {
public:
    YZRect() = default;

    YZRect(float y1, float z1, float y2, float z2, float k, std::shared_ptr<Material<T>> m)
            : AxisAlignedRect<T>(y1, z1, y2, z2, k, X, std::move(m)) {}

};

template<class T>
class XZRect : public AxisAlignedRect<T> {
public:
    XZRect() = default;

    XZRect(float x1, float z1, float x2, float z2, float k, std::shared_ptr<Material<T>> m)
            : AxisAlignedRect<T>(x1, z1, x2, z2, k, Y, std::move(m)) {}

};

#endif //RAYTRACER_RECT_H
