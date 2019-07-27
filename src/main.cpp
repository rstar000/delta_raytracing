#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <omp.h>

#include "image.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "geom.hpp"
#include "camera.hpp"
#include "material.hpp"


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
Vec3 trace(const Ray &ray, const Scene &scene, int maxDepth)
{
    if (maxDepth == 0) 
    {
        return Vec3(0, 0, 0);
    }
    
    TracingResult result = scene.trace(ray);
    
    if (result.obj == nullptr) 
    {
        return Vec3(0,0,0);
    }
    
    Ray new_ray;
    new_ray.direction = sample_mirror(ray.direction, result.normal);
    new_ray.origin = result.position;

    Object* object = result.obj;
    
    float emission = object->getEmission();
    
    Vec3 res_color = Vec3(emission, emission, emission).cwiseProduct(result.color) + result.color.cwiseProduct(trace(new_ray, scene, --maxDepth));
    
    return res_color;
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

    Sphere s1(Vec3(0,0,4), 2.0f, Vec3(1,0,0));
    Sphere s2(Vec3(0,4,2), 0.5f, Vec3(1,1,1));

    s2.setEmission(10);
    scn.add(&s1);
    scn.add(&s2);
    Camera cam(cam_pos, look_at, fov,aspect);


//#pragma omp parallel for private(mt, uniform) schedule(dynamic)
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            xpos = ((x + urand() - width/2)/(width/2));
            ypos = ((y + urand() - height/2)/(height/2));
            Ray r = cam.getRay(xpos,ypos);
            Vec3 pix_color = trace(r,scn,max_depth);
            img(y, x) = pix_color;
        }

        cout << "Row: " << y << endl;
    }

    img.save("output.png");
    return 0;
}