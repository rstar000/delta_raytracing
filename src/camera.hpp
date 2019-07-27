#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "geom.hpp"
#include "ray.hpp"

class Camera
{
    float vfov;
    Vec3 position;
    Vec3 look_at;
    float fov;
    float aspect;
    Vec3 direction;
    Vec3 view_at;
public:
    Camera(float fov, float aspect);

    Camera(Vec3 pos, Vec3 lookAt, float f, float asp)
    {
        position = pos;
        look_at = lookAt;
        fov = f;
        aspect = asp;
        vfov = fov/aspect;
        Vec3 view = look_at - position;
        direction = view.normalized();
    }

    Ray getRay(float a, float b)
    {
        float y = tan(vfov/2) * tan(fov*b*0.5/aspect);
        float x = aspect * tan(vfov/2) * tan(fov*a/2);
 //       float y = tan(vfov/2) * a;
 //       float x = aspect * tan(vfov/2) * b;
        float z = 1.0;
        Ray r;
        r.origin = position;
        r.direction = Vec3(x,y,z);
        return r;
    }
};

