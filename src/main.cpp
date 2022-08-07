#include <iostream>

#include "camera.h"
#include "metal.h"
#include "sphere.h"
#include "utils.h"


constexpr int DEPTH = 10;
constexpr int SPP = 10;

void write(Color c) {
    int ir = static_cast<int>(255.999 * c.r);
    int ig = static_cast<int>(255.999 * c.g);
    int ib = static_cast<int>(255.999 * c.b);
    std::cout << ir << ' ' << ig << ' ' << ib << '\n';
}

Color get_ray_color(const HitList &hitlist, const Ray &r, int depth = DEPTH) {

    if (depth <= 0) return Color(glm::vec3(0));

    HitRecord hr{};
    if (hitlist.hit(r, hr)) {
        Ray scattered{};
        Color attenuation{};
        if (hr.material->scatter(r, hr.point, hr.normal, attenuation, scattered)) {

            return Color(attenuation.getVec()
                         * get_ray_color(hitlist, scattered, depth - 1).getVec());
        }
        return Color(glm::vec3(0));
//        auto N = glm::normalize(hr.point - r.origin());
//        return Color(float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1));
//            auto c = hr.material->color();
//            return c;
    }

    Color c1(1, 1, 1);
    Color c2(.1, .5, .8);
    float t = (r.direction().y + 1) / 2;
    return Color(glm::mix(c1.getVec(), c2.getVec(), t));
}

void render(const HitList &hitlist, const Camera &cam) {

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            glm::vec3 pixel_color(0);
            for (int k = 0; k < SPP; k++) {
                auto u = float(i + Utils::random()) / (IMAGE_HEIGHT - 1);
                auto v = float(j + Utils::random()) / (IMAGE_WIDTH - 1);

                auto r = cam.get_ray(u, v);
                pixel_color += get_ray_color(hitlist, r).getVec();
            }
            pixel_color /= SPP;
            // Gamma correction
            pixel_color = sqrt(pixel_color);
            write(Color(pixel_color));
        }
    }
}

signed main() {

    Camera cam(glm::vec3(1, 0, 0), glm::vec3(0, 0, -2), glm::vec3(0, 1, 0), 90);

    HitList hitlist;
    auto m1 = std::make_shared<Lambertian>(Color(0.2, 0.9, 0.4));
    auto m2 = std::make_shared<Metal>(Color(.2, 0.2, .2), .1);
//    auto s1 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//    auto s2= std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//    auto g = std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1);
    hitlist.add(std::make_shared<Sphere>(glm::vec3(-.5, 0, -1), 0.5, m2));
    hitlist.add(std::make_shared<Sphere>(glm::vec3(.5, 0, -1), 0.5, m2));
    hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1));

    render(hitlist, cam);
    return 0;
}