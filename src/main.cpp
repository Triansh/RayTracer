#include <iostream>
#include <thread>


#include "camera.h"
#include "material_types.h"
#include "sphere.h"
#include "utils.h"
#include "rect.h"
#include "texture.h"
#include "pyramid.h"
#include "box.h"
#include "pdf.h"

constexpr int DEPTH = 80;
constexpr int SPP = 1000;
constexpr int MAX_THREADS = 32;

Utils utils;


auto SolidLambertian = [](Color x) {
    return std::make_shared<Lambertian>(std::make_shared<Solid>(x));
};


class RayTracer {

public:
    RayTracer() {
        image.assign(IMAGE_HEIGHT, std::vector<glm::vec3>(IMAGE_WIDTH, glm::vec3(0)));
        create_scene();
    }

    static void write(Color c) {
        int ir = static_cast<int>(255.999 * c.x);
        int ig = static_cast<int>(255.999 * c.y);
        int ib = static_cast<int>(255.999 * c.z);
        std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }

    Color get_ray_color(const Ray &r, int depth = DEPTH) {
        if (depth <= 0) return glm::vec3(0);

        HitRecord hr{};
        if (hitlist.hit(r, hr)) {
            Ray scattered{};
            Color attenuation{};
            auto emit = hr.material->emittedValue(hr.point, hr.normal, hr.front_face);
            if (hr.material->scatter_ray(r, hr.point, hr.normal, hr.front_face, attenuation, scattered)) {

                if (hr.material->is_specular()) return attenuation * get_ray_color(scattered, depth - 1);

                HittablePdf pdf(light_, hr.point);
                scattered = Ray(hr.point, pdf.random());
                float prob = pdf.probability(scattered.direction());
                return emit +
                       (prob < EPSILON ? glm::vec3(0) : (attenuation * get_ray_color(scattered, depth - 1) / prob));
            }
            return emit;
//        auto N = glm::normalize(hr.point - r.origin());
//        return Color(float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1));
//            auto c = hr.material->color();
//            return c;
        }

//        Color c1(1, 1, 1);
//        Color c2(.1, .5, .8);
//        float t = (r.direction().y + 1) / 2;
//    return c2;
        return {0, 0, 0};
//        return glm::mix(c1, c2, t);
    }

    static void thread_exec(RayTracer *tracer, int rowIndex) {
        for (int j = IMAGE_WIDTH - 1; j >= 0; j--) {
            for (int k = 0; k < SPP; k++) {
                auto u = float(rowIndex + utils.random()) / (IMAGE_HEIGHT - 1);
                auto v = float(j + utils.random()) / (IMAGE_WIDTH - 1);

                auto r = tracer->cam.get_ray(u, v);
                tracer->image[rowIndex][j] += tracer->get_ray_color(r);
            }
            tracer->image[rowIndex][j] /= SPP;
            // Gamma correction
            tracer->image[rowIndex][j] = sqrt(tracer->image[rowIndex][j]);
        }
    }

    void render() {

        std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";
        std::vector<std::thread> ts;
        for (int i = IMAGE_HEIGHT - 1; i >= 0; i -= MAX_THREADS) {
            std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
            for (int j = 0; j < MAX_THREADS; j++) {
                ts.emplace_back(thread_exec, this, i - j);
            }
            for (auto &thr: ts) thr.join();
            ts.clear();
            for (int j = 0; j < MAX_THREADS; j++) {
                for (int k = IMAGE_HEIGHT - 1; k >= 0; k--) {
                    write(image[i - j][k]);
                }
            }
        }

    }

    void create_scene() {

        {
            cam = Camera(glm::vec3(288, 250, -450), glm::vec3(278, 250, 0), glm::vec3(0, 1, 0), 54);
//            cam = Camera(glm::vec3(278, 554, 279.5), glm::vec3(278, 553, 279.5), glm::vec3(1, 0, 0), 90);
//
            auto red = SolidLambertian(Color(.65, .05, .05));
            auto green = SolidLambertian(Color(.12, .45, .15));
//            auto purp = SolidLambertian(Color(0.7, 0.3, 0.75));
            auto iron = std::make_shared<Metal>(std::make_shared<Solid>(Color(0.8, 0.85, 0.88)), 0);
            auto white = SolidLambertian(Color(.95, .9, .85));
            auto purp = SolidLambertian(Color(0.7, 0.3, 0.75));
//            auto blue_glass = SolidLambertian(Color(0.1373, .6745, .7686));
            auto blue_glass = std::make_shared<Transparent>(std::make_shared<Solid>(Color(0.1373, .6745, .7686)));


            auto yellow = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
            auto blue = std::make_shared<Solid>(Color(0.1, 0.1, 0.9));
            auto checker = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue, yellow, .05));
            auto light = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 60);

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
                                (glm::vec3(400, 280, 300), 80, blue_glass));
            hitlist.add(std::make_shared<Pyramid<Metal>>
                                (70, 320, 220, 400, 0, 200, iron));
            hitlist.add(std::make_shared<Box<Lambertian>>
                                (glm::vec3(250, 0, 250), glm::vec3(480, 100, 480), purp));

            light_ = std::make_shared<XZRect<DiffusedLight>>
                    (213, 227, 343, 332, 554, light, true);
            hitlist.add(light_); // light
        }

        {
//            cam = Camera(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 90);
//
//            auto material_ground = SolidLambertian(Color(0.8, 0.8, 0.0));
//            auto material_center = SolidLambertian(Color(0.7, 0.3, 0.3));
//            auto material_left = std::make_shared<Metal>(std::make_shared<Solid>(Color(0.85, 0, 0.8)), 0.3);
//            auto light = std::make_shared<DiffusedLight>(std::make_shared<Solid>(Color(1, 1, 1)), 25);
////        auto yellow = std::make_shared<Solid>(Color(0.8, 0.75, 0.3));
////        auto blue = std::make_shared<Solid>(Color(0.2, 0.3, 0.8));
////        auto checker = std::make_shared<Lambertian>(std::make_shared<CheckerBoard>(blue, yellow, 5));
//            auto material_right = std::make_shared<Lambertian>(std::make_shared<Solid>(Color(0.8, 0.6, 0.2)));
//
//            hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(0.0, -100.5, 1.0), 100.0, material_right));
//            hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(0.0, 0.0, 1.0), 0.5, material_center));
//            hitlist.add(std::make_shared<Sphere<Lambertian>>(glm::vec3(1.0, 0.0, 1.0), 0.5, material_ground));
//            hitlist.add(std::make_shared<Sphere<Metal>>(glm::vec3(-1.0, 0.0, 1.0), 0.5, material_left));
//
//            light_ = std::make_shared<XZRect<DiffusedLight>>(-1.5, -1, 1.5, 1, 1, light);
//            hitlist.add(light_); // light

//        auto m1 = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.4));
//        auto m2 = std::make_shared<Metal>(Color(1, 0, 1), 0);
//        auto s1 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//        auto s2 = std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2);
//        auto g = std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1);
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, m2));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(.5, 0, -1), 0.5, m2));
//        hitlist.add(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, m1));
        }
    }


private:
    std::vector<std::vector<glm::vec3>> image;
    HitList hitlist;
    Camera cam;
    std::shared_ptr<BaseHittable> light_;

};

signed main() {

    auto tracer = RayTracer();
    tracer.render();

    return 0;
}
