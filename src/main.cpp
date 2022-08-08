#include <iostream>

#include "camera.h"
#include "metal.h"
#include "sphere.h"
#include "utils.h"
#include "rect.h"
#include "texture.h"

constexpr int DEPTH = 10;
constexpr int SPP = 100;

Utils utils;


auto SolidLambertian = [](Color x) {
    return std::make_shared<Lambertian>(std::make_shared<Solid>(x));
};


void write(Color c) {
    int ir = static_cast<int>(255.999 * c.x);
    int ig = static_cast<int>(255.999 * c.y);
    int ib = static_cast<int>(255.999 * c.z);
    std::cout << ir << ' ' << ig << ' ' << ib << '\n';
}

Color get_ray_color(const HitList &hitlist, const Ray &r, int depth = DEPTH) {

    if (depth <= 0) return glm::vec3(0);

    HitRecord hr{};
    if (hitlist.hit(r, hr)) {
        Ray scattered{};
        Color attenuation{};
        auto emit = hr.material->emit(hr.point);
        if (hr.material->scatter(r, hr.point, hr.normal, attenuation, scattered)) {

            return Color(emit +
                         (attenuation
                          * get_ray_color(hitlist, scattered, depth - 1)));
        }
        return emit;
//        auto N = glm::normalize(hr.point - r.origin());
//        return Color(float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1));
//            auto c = hr.material->color();
//            return c;
    }

    Color c1(1, 1, 1);
    Color c2(.1, .5, .8);
    float t = (r.direction().y + 1) / 2;
//    return c2;
    return {0, 0, 0};
    return glm::mix(c1, c2, t);
}

void render(const HitList &hitlist, const Camera &cam) {

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int i = IMAGE_HEIGHT - 1; i >= 0; i--) {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = IMAGE_WIDTH - 1; j >= 0; j--) {
            glm::vec3 pixel_color(0);
            for (int k = 0; k < SPP; k++) {
                auto u = float(i + utils.random()) / (IMAGE_HEIGHT - 1);
                auto v = float(j + utils.random()) / (IMAGE_WIDTH - 1);

                auto r = cam.get_ray(u, v);
                pixel_color += get_ray_color(hitlist, r);
            }
            pixel_color /= SPP;
            // Gamma correction
            pixel_color = sqrt(pixel_color);
            write(Color(pixel_color));
        }
    }
}

signed main() {

    Camera cam;

    HitList hitlist;
//    {
//        cam = Camera(glm::vec3(278, 278, -400), glm::vec3(278, 278, 0), glm::vec3(0, 1, 0), 54);
//
//        auto red = SolidLambertian(Color(.65, .05, .05));
//        auto green = SolidLambertian(Color(.12, .45, .15));
//        auto purp = SolidLambertian(Color(0.7, 0.3, 0.75));
        auto white = SolidLambertian(Color(.73, .73, .73));

        auto yellow = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
        auto blue = std::make_shared<Solid>(Color(0.2, 0.3, 0.8));
        auto checker = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue, yellow, 5));
//
        auto light = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 15);
//
//        hitlist.add(std::make_shared<YZRect>(0, 0, 555, 555, 0, red)); // left wall
//        hitlist.add(std::make_shared<YZRect>(0, 0, 555, 555, 555, green)); // right wall
//
        hitlist.add(std::make_shared<XZRect>(0, 0, 555, 555, 0, checker)); // ground
        hitlist.add(std::make_shared<XZRect>(0, 0, 555, 555, 555, white)); // roof
//        hitlist.add(std::make_shared<XYRect>(0, 0, 555, 555, 555, white)); // front wall
//
//        hitlist.add(std::make_shared<XZRect>(213, 227, 343, 332, 554, light));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(240, 280, 300), 100, purp));
//
//    }

    {
//        cam = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -2), glm::vec3(0, 1, 0), 90);
//
//        auto material_ground = SolidLambertian(Color(0.8, 0.8, 0.0));
////        auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
//        auto material_left = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(0.8, 0.8, 0.8)), 5);
//        auto yellow = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
//        auto blue = std::make_shared<Solid>(Color(0.2, 0.3, 0.8));
//        auto checker = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue, yellow, 5));
////        auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);
//
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0.0, -100.5, -1.0), 100.0, checker));
////        hitlist.add(std::make_shared<Sphere>(glm::vec3(0.0, 0.0, -1.0), 0.5, material_center));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(1.0, 0.0, -1.0), 0.5, material_ground));

//        auto m1 = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.4));
//        auto m2 = std::make_shared<Metal>(Color(1, 0, 1), 0);
//        auto s1 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//        auto s2 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//        auto g = std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1);
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(.5, 0, -1), 0.5, m2));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1));
    }

    render(hitlist, cam);
    return 0;
}