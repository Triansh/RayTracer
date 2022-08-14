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
constexpr int SPP = 100;
//constexpr int MAX_THREADS = 40;


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
            for (int j = 0; j < IMAGE_WIDTH; j++) {
//                for (int j = IMAGE_WIDTH - 1; j >= 0; j--) {
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
        if (hitlist.hit_by_ray(r, hr, infinity)) {
            Ray scattered{};
            Color attenuation{};
            auto emit = hr.material->emittedValue(hr.point, hr.normal, hr.front_face);
            if (hr.material->scatter_ray(r, hr.point, hr.normal, hr.front_face, attenuation, scattered)) {

                if (hr.material->is_specular()) return attenuation * get_ray_color(scattered, depth - 1);
//
                HittablePdf pdf(light_, hr.point, hr.normal);
                scattered = Ray(hr.point, pdf.random());
                float prob = pdf.probability(scattered.direction());
                return emit +
                       (prob < EPSILON ? glm::vec3(0) : (attenuation * get_ray_color(scattered, depth - 1) / prob));

                return emit + attenuation * get_ray_color(scattered, depth - 1);

            }
            return emit;
//        auto N = glm::normalize(hr.normal);
//        return Color(float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1));
//            auto c = hr.material->color();
//            return c;
        }

//        Color c1(1, 1, 1);
//        Color c2(.1, .5, .8);
//        float t = (r.direction().y + 1) / 2;
//        return c2;
        return {0, 0, 0};
//        return glm::mix(c1, c2, t);
    }

    void render() {

        std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

#pragma omp parallel for
        for (int j = IMAGE_WIDTH - 1; j >= 0; j--) {
            for (int i = IMAGE_HEIGHT - 1; i >= 0; i--) {
                for (int k = 0; k < SPP; k++) {
                    auto u = float(i + utils.random()) / (IMAGE_HEIGHT - 1);
                    auto v = float(j + utils.random()) / (IMAGE_WIDTH - 1);
                    auto r = cam.get_ray(u, v);
                    image[j][i] += get_ray_color(r);
                }

            }
            std::cerr << "Done with " << j << "\n";
        }
        std::cerr << "All done!\n";
    }

    void create_scene() {


        switch (1) {
            case 1: {
                cam = Camera(glm::vec3(278, 278, -550), glm::vec3(278, 278, 0), glm::vec3(0, 1, 0), 54);
//
                auto red = SolidLambertian(Color(.65, .05, .05));
                auto green = SolidLambertian(Color(.12, .45, .15));
                auto iron = std::make_shared<Metal>(std::make_shared<Solid>(Color(0.6314, 0.6157, 0.5804)), 0);
                auto white = SolidLambertian(Color(.95, .9, .85));
                auto purp = SolidLambertian(Color(0.7, 0.3, 0.75));
                auto blue_glass = SolidLambertian(Color(0.1373, .6745, .7686));
                auto transparent = std::make_shared<Transparent>();

                //0.1373, .6745, .7686

                auto yellow = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
                auto blue = std::make_shared<Solid>(Color(0.1, 0.1, 0.9));
                auto checker = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue, yellow, .05));
                auto light = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 5);

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
                hitlist.add(std::make_shared<Sphere<Transparent>>
                                    (glm::vec3(300, 80, 70), 80, transparent, false));
                hitlist.add(std::make_shared<Pyramid<Metal>>
                                    (370, 320, 520, 450, 0, 250, iron));
                hitlist.add(std::make_shared<Box<Lambertian>>
                                    (glm::vec3(50, 0, 300), glm::vec3(280, 200, 510), purp));

                light_ = std::make_shared<XZRect<DiffusedLight>>
                        (213, 227, 343, 332, 554, light, false);
                hitlist.add(light_); // light
                break;
            }
            case 2: {
                cam = Camera(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 90);

                auto material_ground = SolidLambertian(Color(0.8, 0.8, 0.0));
                auto material_center = SolidLambertian(Color(0.7, 0.3, 0.3));
                auto material_left = std::make_shared<Metal>(std::make_shared<Solid>(Color(0.85, 0, 0.8)), 0.3);
                auto yellow2 = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
                auto blue2 = std::make_shared<Solid>(Color(0.2, 0.3, 0.8));
                auto checker1 = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue2, yellow2, 5));
                auto material_right = std::make_shared<Lambertian>(std::make_shared<Solid>(Color(0.8, 0.6, 0.2)));
//
                hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(0.0, -100.5, 1.0), 100.0, material_right));
                hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(0.0, 0.0, 1.0), 0.5, material_center));
                hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(1.0, 0.0, 1.0), 0.5, material_ground));
                hitlist.add(std::make_shared<Sphere<Metal>>(glm::vec3(-1.0, 0.0, 1.0), 0.5, material_left));

                auto light_color = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 7);
                light_ = std::make_shared<XZRect<DiffusedLight>>(-1.5, -1, 1.5, 1, 1, light_color);
                hitlist.add(light_); // light

//        auto m1 = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.4));
//        auto m2 = std::make_shared<Metal>(Color(1, 0, 1), 0);
//        auto s1 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//        auto s2 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//        auto g = std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1);
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(.5, 0, -1), 0.5, m2));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1));
                break;
            }
            case 3: {
                cam = Camera(glm::vec3(478, 278, -600), glm::vec3(278, 278, 0), glm::vec3(0, 1, 0), 40);

                auto ground = SolidLambertian(Color(0.48, 0.83, 0.53));

//                const int boxes_per_side = 20;
//                for (int i = 0; i < boxes_per_side; i++) {
//                    for (int j = 0; j < boxes_per_side; j++) {
//                        auto w = 100.0;
//                        auto x0 = -1000.0 + i * w;
//                        auto z0 = -1000.0 + j * w;
//                        auto y0 = 0.0;
//                        auto x1 = x0 + w;
//                        auto y1 = Utils::random(1, 101);
//                        auto z1 = z0 + w;
//
//                        hitlist.add(std::make_shared<Box<Lambertian>>(glm::vec3(x0, y0, z0), glm::vec3(x1, y1, z1),
//                                                                      ground));
//                    }
//                }


                auto light_color = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 15);
                light_ = std::make_shared<XZRect<DiffusedLight>>(123, 147, 423, 412, 554, light_color, false);
                hitlist.add(light_);

//                auto center1 = point3(400, 400, 200);
//                auto center2 = center1 + vec3(30,0,0);
//                auto moving_sphere_material = SolidLambertian(Color (0.7, 0.3, 0.1));
//                hitlist.add(std::make_shared<Sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

                auto trans = std::make_shared<Transparent>();
                hitlist.add(std::make_shared<Sphere<Transparent>>(glm::vec3(260, 150, 45), 50, trans));
                hitlist.add(std::make_shared<Sphere<Metal>>(
                        glm::vec3(0, 150, 145), 50,
                        std::make_shared<Metal>(std::make_shared<Solid>(Color(0.8, 0.8, 0.9)), 1.0)
                ));

                auto boundary = std::make_shared<Sphere<Transparent>>(glm::vec3(360, 150, 145), 70, trans);
                hitlist.add(boundary);
                boundary = std::make_shared<Sphere<Transparent>>(glm::vec3(0, 0, 0), 5000, trans);

                auto white2 = SolidLambertian(Color(.73, .73, .73));
//                int ns = 1000;
//                for (int j = 0; j < ns; j++) {
//                    hitlist.add(std::make_shared<Sphere<Lambertian>>(Utils::random_vec3(0, 165), 10, white2));
//                }
                break;
            }
            case 4: {
                cam = Camera(glm::vec3(13, 2, 3), glm::vec3(0), glm::vec3(0, 1, 0), 20);
//                auto checker = std::make_shared<CheckerBoard>(std::make_shared<Solid>(Color(0.2, 0.3, 0.1)), std::make_shared<Solid>((Color(0.9, 0.9, 0.9))));
                auto ground_material = SolidLambertian(Color(0.5, 0.5, 0.5));
                hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(0, -1000, 0), 1000, ground_material));

                for (int a = -4; a < 4; a++) {
                    for (int b = -4; b < 4; b++) {
                        auto choose_mat = utils.random();
                        glm::vec3 center(a + 0.9 * Utils::random(0, 1), 0.2, b + 0.9 * Utils::random(0, 1));

                        if (glm::length(center - glm::vec3(4, 0.2, 0)) > 0.9) {

                            if (choose_mat < 0.8) {
                                // diffuse
                                auto albedo = utils.random_vec3() * utils.random_vec3();
                                auto sphere_material = SolidLambertian(albedo);
                                auto center2 = center + glm::vec3(0, Utils::random(0, .5), 0);
                                hitlist.add(std::make_shared<Sphere<Lambertian>>(center, .2, sphere_material));
                            } else if (choose_mat < 0.95) {
                                // metal
                                auto albedo = Utils::random_vec3(0.5, 1);
                                auto fuzz = Utils::random(0, 0.5);
                                auto sphere_material = std::make_shared<Metal>(std::make_shared<Solid>(albedo), fuzz);
                                hitlist.add(std::make_shared<Sphere<Metal>>(center, 0.2, sphere_material));
                            } else {
                                // glass
                                auto sphere_material = std::make_shared<Transparent>();
                                hitlist.add(std::make_shared<Sphere<Transparent>>(center, 0.2, sphere_material));
                            }
                        }
                    }
                }

                auto material1 = std::make_shared<Transparent>();
                hitlist.add(std::make_shared<Sphere<Transparent>>(glm::vec3(0, 1, 0), 1.0, material1, false));

                auto material2 = SolidLambertian(Color(0.4, 0.2, 0.1));
                hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(-4, 1, 0), 1.0, material2));

                auto material3 = std::make_shared<Metal>(std::make_shared<Solid>(Color(0.7, 0.6, 0.5)), 0.0);
                hitlist.add(std::make_shared<Sphere<Metal>>(glm::vec3(4, 1, 0), 1.0, material3));

//                return hittable_list(std::make_shared<bvh_node>(world, 0.0, 1.0));
            }

//                hitlist.add(std::make_shared<translate>(
//                                    std::make_shared<rotate_y>(
//                                            std::make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
//                                    vec3(-100,270,395)
//                            )
//                );
        }
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
