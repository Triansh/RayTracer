#include <iostream>

#include "camera.h"
#include "metal.h"
#include "sphere.h"
#include "utils.h"
#include "rect.h"


constexpr int DEPTH = 100;
constexpr int SPP = 1000;

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
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            glm::vec3 pixel_color(0);
            for (int k = 0; k < SPP; k++) {
                auto u = float(i + Utils::random()) / (IMAGE_HEIGHT - 1);
                auto v = float(j + Utils::random()) / (IMAGE_WIDTH - 1);

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
    {
        cam = Camera(glm::vec3(278, 278, -800), glm::vec3(278, 278, 0), glm::vec3(0, 1, 0), 54);

        auto red = std::make_shared<Lambertian>(Color(.65, .05, .05));
        auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
        auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
        auto light = std::make_shared<DiffusedLight>(Color(1, 1, 1), 15);

//        hitlist.add(std::make_shared<XYRect>(-1, -4, +1, +4, 100, red));
        hitlist.add(std::make_shared<YZRect>(0, 0, 555, 555, 555, red));
        hitlist.add(std::make_shared<YZRect>(0, 0, 555, 555, 0, green));
        hitlist.add(std::make_shared<XZRect>(150, 150, 400, 400, 554, light));
        hitlist.add(std::make_shared<XZRect>(0, 0, 555, 555, 0, white));
        hitlist.add(std::make_shared<XZRect>(0, 0, 555, 555, 555, white));
        hitlist.add(std::make_shared<XYRect>(0, 0, 555, 555, 555, white));
    }

    {
//        cam = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -2), glm::vec3(0, 1, 0), 90);
//
//        auto red = std::make_shared<Lambertian>(Color(.65, .05, .05));
//        auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
//        auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
//        auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
//        auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);
//
//        hitlist.add(std::make_shared<XYRect>(-1, -4, 1, 4, -2, red));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0.0, -100.5, -1.0), 100.0, material_ground));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0.0, 0.0, -1.0), 0.5, material_center));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(1.0, 0.0, -1.0), 0.5, material_right));

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