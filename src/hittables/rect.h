//
// Created by trios on 8/7/22.
//

#ifndef RAYTRACER_RECT_H
#define RAYTRACER_RECT_H

#include "utils/utils.h"

#include "hittables/hittable.h"


template<class T>
class AxisAlignedRect : public Hittable<T, AxisAlignedRect> {

public:
    AxisAlignedRect() : material_(nullptr) {}

    AxisAlignedRect(float x1, float y1, float x2, float y2, float k, Axis ax, std::shared_ptr<Material<T>> m,
                    bool flip = false)
            : material_(m), x1_(x1), x2_(x2), y1_(y1), y2_(y2), k_(k), axis(ax), flip_(flip) {

        area_ = (x2 - x1) * (y2 - y1);
        const static std::uniform_real_distribution<float> random_x_distribution(x1, x2);
        const static std::mt19937 random_x_generator;
        randomizer_x = std::bind(random_x_distribution, random_x_generator);

        const static std::uniform_real_distribution<float> random_y_distribution(y1, y2);
        const static std::mt19937 random_y_generator;
        randomizer_y = std::bind(random_y_distribution, random_y_generator);
    }

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
            hr.set_face_normal(r, glm::vec3(1, 0, 0));
        } else if (axis == Y) {
            if (!(x1_ <= hit_point.x and hit_point.x <= x2_ and y1_ <= hit_point.z and hit_point.z <= y2_))
                return false;
            hr.set_face_normal(r, glm::vec3(0, 1, 0));
        } else if (axis == Z) {
            if (!(x1_ <= hit_point.x and hit_point.x <= x2_ and y1_ <= hit_point.y and hit_point.y <= y2_))
                return false;
            hr.set_face_normal(r, glm::vec3(0, 0, 1));
        }

        hr.point = hit_point;
        hr.time = t;
        hr.material = material_;
        if (flip_) hr.front_face = !hr.front_face;
        return true;
    }

    float get_probability(glm::vec3 dir, glm::vec3 point) const {
        HitRecord hr;
        if (!hit(Ray(point, dir), hr, float(LONG_LONG_MAX)))
            return 0;

        auto distance_squared = hr.time * hr.time;
        auto cosine = std::fabs(glm::dot(dir, hr.normal));
        if (cosine < EPSILON) return 0;

        return distance_squared / (cosine * area_);
    }

    glm::vec3 get_random(const glm::vec3 &point) const {
        auto x = randomizer_x(), y = randomizer_y();
        glm::vec3 random_point;
        if (axis == X) {
            random_point = {k_, x, y};
        } else if (axis == Y) {
            random_point = {x, k_, y};
        } else if (axis == Z) {
            random_point = {x, y, k_};
        }
        return random_point - point;
    }

protected:
    std::shared_ptr<Material<T>> material_;
    float x1_{}, y1_{};
    float x2_{}, y2_{};
    float k_{};
    Axis axis;
    float area_;
    bool flip_;
private:
    std::function<float()> randomizer_x;
    std::function<float()> randomizer_y;
};

template<class T>
class XYRect : public AxisAlignedRect<T> {
public:
    XYRect() = default;

    XYRect(float x1, float y1, float x2, float y2, float k, std::shared_ptr<Material<T>> m, bool flip = false)
            : AxisAlignedRect<T>(x1, y1, x2, y2, k, Z, std::move(m), flip) {}
};


template<class T>
class YZRect : public AxisAlignedRect<T> {
public:
    YZRect() = default;

    YZRect(float y1, float z1, float y2, float z2, float k, std::shared_ptr<Material<T>> m, bool flip = false)
            : AxisAlignedRect<T>(y1, z1, y2, z2, k, X, std::move(m), flip) {}

};

template<class T>
class XZRect : public AxisAlignedRect<T> {
public:
    XZRect() = default;

    XZRect(float x1, float z1, float x2, float z2, float k, std::shared_ptr<Material<T>> m, bool flip = false)
            : AxisAlignedRect<T>(x1, z1, x2, z2, k, Y, std::move(m), flip) {}

};

#endif //RAYTRACER_RECT_H
