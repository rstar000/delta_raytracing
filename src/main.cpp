#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <omp.h>

#include "image.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "geom.hpp"


using Eigen::MatrixXd;

using Vec3 = Eigen::Vector3f;
using Quat = Eigen::Quaternionf;

using std::cout;
using std::endl;

std::mt19937 mt;
std::uniform_real_distribution<float> uniform(0.0f, 1.0f);

float urand()
{
    return uniform(mt);
}

// Trace a ray into the scene. This is a recursive function
// that calculates light intensity and color along a path
Vec3 trace(const Ray &ray, const Scene &scene, int depth)
{
    return Vec3();
}


// Input is the pixel offset, output is the appropriate coordinate
// on the image plane
Vec3 cam_direction(float angle_x, float angle_y, float fov, float aspect)
{
    return Vec3();
}

int main()
{
    // Rendering parameters
    size_t width = 512;
    size_t height = 512;
    int max_depth = 8;
    int spp = 300;
    float aspect = height / width;
    float fov = 2 * M_PI / 3;

    // Camera parameters
    Vec3 cam_pos(0, 0, 0);
    Vec3 look_at(0, 0, -1);
    float xpos;
    float ypos;
    Image<RGBPixel> img(width, height);
    Scene scn;
    Camera cam(cam_pos, look_at, fov,aspect);

    //test_triangle();

#pragma omp parallel for private(mt, uniform) schedule(dynamic)
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float a = (float(x) - width / 2) / (width / 2);
            float b = (float(y) - height / 2) / (height / 2);
            Ray ray = camera.getRay(a, b);
//            cout << "Direction\n" << ray.direction << endl;
//            Vec3 pix_color(a, b, 1);
            float d = ray.direction.normalized().dot(Vec3(0,0,1));
//            cout << "Dot: " << d << endl;
            Vec3 pix_color(d,d,d);
            img(y, x) = pix_color;
        }

        cout << "Row: " << y << endl;
    }

    img.save("output.png");
    return 0;
}
