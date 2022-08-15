#include <iostream>
#include <thread>
#include <omp.h>


#include "camera.h"
#include "materials/material_types.h"
#include "hittables/sphere.h"
#include "utils/utils.h"
#include "hittables/rect.h"
#include "common/texture.h"
#include "hittables/pyramid.h"
#include "hittables/box.h"
#include "utils/pdf.h"
#include "utils/bvh.h"

constexpr int DEPTH = 50;
constexpr int SPP = 1000;


Utils utils;
float infinity = std::numeric_limits<float>::infinity();


auto SolidLambertian = [](Color x) {
    return std::make_shared<Lambertian>(std::make_shared<Solid>(x));
};


class RayTracer {

public:
    RayTracer() {
        image.assign(IMAGE_HEIGHT, std::vector<glm::vec3>(IMAGE_WIDTH, glm::vec3(0)));
        create_scene();
    }

    void write() {

        for (int i = IMAGE_HEIGHT - 1; i >= 0; i--) {
//            for (int j = 0; j < IMAGE_WIDTH; j++) {
            for (int j = IMAGE_WIDTH - 1; j >= 0; j--) {
                auto c = image[j][i];

                if (c.x != c.x) c.x = 0;
                if (c.y != c.y) c.y = 0;
                if (c.z != c.z) c.z = 0;

                // Gamma correction
                c = sqrt(c / float(SPP));

                int r = static_cast<int>(255.999 * c.x);
                int g = static_cast<int>(255.999 * c.y);
                int b = static_cast<int>(255.999 * c.z);
                std::cout << r << ' ' << g << ' ' << b << '\n';
            }
        }

    }

    Color get_ray_color(const Ray &r, int depth = DEPTH) {
        if (depth <= 0) return glm::vec3(0);

        HitRecord hr{};
//        if (hitlist.hit_by_ray(r, hr, infinity)) {
        if (root_->hit_by_ray(r, hr, infinity)) {
            Ray scattered{};
            Color attenuation{};
            auto emit = hr.material->emittedValue(hr.point, hr.normal, hr.front_face);
            if (hr.material->scatter_ray(r, hr.point, hr.normal, hr.front_face, attenuation, scattered)) {

//                if (hr.material->is_specular()) return attenuation * get_ray_color(scattered, depth - 1);

//                InverseSquareLightPdf pdf(light_, hr.point, hr.normal);
//                scattered = Ray(hr.point, pdf.random());
//                float prob = pdf.probability(scattered.direction());
//                return emit +
//                       (prob < EPSILON ? glm::vec3(0) : (attenuation * get_ray_color(scattered, depth - 1) / prob));

                return emit + attenuation * get_ray_color(scattered, depth - 1);

            }
            return emit;
//            auto N = glm::normalize(hr.normal);
//            return Color(float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1));
        }
        return glm::vec3(0);
    }

    void render() {

        std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

#pragma omp parallel num_threads(12)
        {
#pragma omp for schedule(static, 1)
            for (int j = IMAGE_WIDTH - 1; j >= 0; j--) {
                for (int i = IMAGE_HEIGHT - 1; i >= 0; i--) {
                    for (int k = 0; k < SPP; k++) {
                        auto u = float(i + utils.random()) / (IMAGE_HEIGHT - 1);
                        auto v = float(j + utils.random()) / (IMAGE_WIDTH - 1);
                        auto r = cam.get_ray(u, v);
                        image[j][i] += get_ray_color(r);
                    }

                }
//                std::cerr << "Done with " << j << "\n";
            }
        }
        std::cerr << "All done!\n";
    }

    void create_scene() {


        cam = Camera(glm::vec3(278, 278, -700), glm::vec3(278, 278, 0), glm::vec3(0, 1, 0), 45);
//                cam = Camera(glm::vec3(278, 554, 279.5), glm::vec3(278, 553, 279.5), glm::vec3(1, 0, 0), 90);
//                cam = Camera(glm::vec3(278, 550, 278), glm::vec3(278, 0, 278), glm::vec3(0, 1, 0), 50);
//
        auto red = SolidLambertian(Color(.65, .05, .05));
        auto green = SolidLambertian(Color(.12, .45, .15));
        auto iron = std::make_shared<Metal>(std::make_shared<Solid>(Color(1, .843, 0)), 0.);
        auto orange = SolidLambertian(Color(1, 0.5, 0.313));
        auto violet = SolidLambertian(Color(0.561, 0.0, 1));
        auto white = SolidLambertian(Color(.95, .9, .85));
        auto purp = SolidLambertian(Color(0.7, 0.3, 0.75));
        auto blue_glass = SolidLambertian(Color(0.1373, .6745, .7686));
        auto transparent = std::make_shared<Transparent>();

        //0.1373, .6745, .7686
        //0.6314, 0.6157, 0.5804

        auto yellow = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
        auto blue = std::make_shared<Solid>(Color(0.1, 0.1, 0.9));
        auto checker = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue, yellow, .05));
        auto light = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 15);

        hitlist.add(std::make_shared<YZRect<Lambertian>>
                            (0, 0, 555, 555, 0, red)); // left wall
        hitlist.add(std::make_shared<YZRect<Lambertian>>
                            (0, 0, 555, 555, 555, green)); // right wall
        hitlist.add(std::make_shared<XZRect<Lambertian>>
                            (0, 0, 555, 555, 0, checker)); // ground
        hitlist.add(std::make_shared<XZRect<Lambertian>>
                            (0, 0, 555, 555, 555, white)); // roof
        hitlist.add(std::make_shared<XYRect<Lambertian>>
                            (0, 0, 555, 555, 555, white)); // front wall
//        hitlist.add(std::make_shared<Sphere<Transparent>>
//                            (glm::vec3(300, 80, 70), 80, transparent));
                hitlist.add(std::make_shared<Sphere<Lambertian>>
                                    (glm::vec3(300, 80, 70), 80, blue_glass));
                hitlist.add(std::make_shared<Pyramid<Lambertian>>
                                    (370, 320, 520, 450, 0, 250, violet));
//        hitlist.add(std::make_shared<Box<Lambertian>>(glm::vec3(50, 0, 300), glm::vec3(280, 200, 510), purp));
//        hitlist.add(std::make_shared<Pyramid<Metal>>
//                            (370, 320, 520, 450, 0, 250, iron));
        hitlist.add(std::make_shared<Box<Lambertian>>(glm::vec3(50, 0, 300), glm::vec3(280, 200, 510), orange));

        light_ = std::make_shared<XZRect<DiffusedLight>>
                (213, 227, 343, 332, 554, light, false);
        hitlist.add(light_); // light

        root_ = std::make_shared<BVHNode>(hitlist.hittables, 0, hitlist.hittables.size());

    }


private:
    std::vector<std::vector<glm::vec3>> image;
    HitList hitlist;
    Camera cam;
    std::shared_ptr<BaseHittable> light_;
    std::shared_ptr<BVHNode> root_;

};

signed main() {

    auto tracer = RayTracer();
    tracer.render();
    tracer.write();

    return 0;
}
