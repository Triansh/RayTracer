//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_RECT_H
#define RAYTRACER_RECT_H

#include <utility>

#include "hittable.h"

class Rect : public Hittable {
public:
    Rect(): Hittable(nullptr) {}
    explicit Rect(std::shared_ptr<Material> m) : Hittable(std::move(m)) {}

    bool hit(const Ray &r, HitRecord &hr, float max_time) const override = 0;
};

class XYRect : public Rect {
public:
    XYRect() = default;

    XYRect(float x1, float y1, float x2, float y2, float k, std::shared_ptr<Material> m)
            : Rect(std::move(m)), x1_(x1), y1_(y1), x2_(x2), y2_(y2), k_(k) {}

    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;

private:
    float x1_, y1_;
    float x2_, y2_;
    float k_;

};

class YZRect : public Rect {
public:
    YZRect() = default;

    YZRect(float y1, float z1, float y2, float z2, float k, std::shared_ptr<Material> m)
            : Rect(std::move(m)), z1_(z1), y1_(y1), z2_(z2), y2_(y2), k_(k) {}

    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;

private:
    float z1_, y1_;
    float z2_, y2_;
    float k_;

};


class XZRect : public Rect {
public:
    XZRect() = default;

    XZRect(float x1, float z1, float x2, float z2, float k, std::shared_ptr<Material> m)
            : Rect(std::move(m)), x1_(x1), z1_(z1), x2_(x2), z2_(z2), k_(k) {}

    bool hit(const Ray &r, HitRecord &hr, float max_time) const override;

private:
    float x1_, z1_;
    float x2_, z2_;
    float k_;

};

#endif //RAYTRACER_RECT_H
