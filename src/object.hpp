#pragma once

#include <cmath>
#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Core>

#include "ray.hpp"
#include "geom.hpp"

#include <math.h>

using Vec3 = Eigen::Vector3f;
using Quat = Eigen::Quaternionf;
using Mat4x4 = Eigen::Matrix4f;

class Object;

enum Material
{
    DIFFUSE = 0,
    GLOSSY = 1,
    MIRROR = 2,
    GLASS = 3,
    METALLIC = 4
};


struct TracingResult
{
    /* Vectors in world space origin + distance * direction*/
    Vec3 position;
    /* Unit normal in world space */
    Vec3 normal;
    /* Surface color. RGB normalized [0,1]*/
    Vec3 color;
    /* Distance from ray origin to object */
    float distance = -1;

    Object *obj = nullptr;
};


inline bool tracing_success(const TracingResult &r) 
{
    return r.distance > 0;
}

class Object
{
public:
    Object() {}
    virtual ~Object() {}

    virtual TracingResult Trace(const Ray &r) = 0;

    float getEmission () 
    {
        return emission;
    }

    Material getMaterial() 
    {
        return material;
    }

    void setEmission(float emission)
    {
        this->emission = emission;
    }

    void setMaterial(Material material) 
    {
        this->material = material;
    }
    
protected:
    float emission = 0;
    Material material = DIFFUSE;
};


class Plane : public Object
{
public:
    Plane(Vec3 n, float d, Vec3 color) : 
        n(n), l(d), color(color)
    {

    }

    TracingResult Trace(const Ray &r) {
        // d = r.direction
        // p - r.origin
        float nd = n.dot(r.direction);
        if (nd == 0){
            return TracingResult();
        } else{
            float alfa = (l-n.dot(r.origin))/nd;
            TracingResult res;
            res.position = r.origin + alfa*r.direction;
            res.color = color;
            res.normal = n;
            res.distance = alfa;
            res.obj = this;

            return res;
        }
    }

private:
    Vec3 n;
    float l;
    Vec3 color;
};


class Sphere : public Object
{
public:
    Sphere(Vec3 center, float radius, Vec3 color) :
        center(center), radius(radius), color(color)
    {}

    TracingResult Trace(const Ray &r) {
        Vec3 z = r.origin - center;

        TracingResult result;

        float dz = r.direction.dot(z);
        float distance;
        float determinant = dz - r.direction.dot(r.direction) * (z.dot(z) - radius);

        if (determinant >= 0) 
        {
            determinant = sqrt(determinant);

            float distanceOne = -2 * dz + determinant;
            float distanceTwo = -2 * dz - determinant;

            if (distanceOne > 0 && distanceTwo > 0)
            {
                distance = distanceTwo;
            }
            else if (std::max(distanceOne, distanceTwo) > 0) {
                distance = distanceOne;
            }
            else {
                return result;
            }

            result.position = r.origin + distance * r.direction;
            result.color = color;
            result.distance = distance;
            result.normal = (result.position - center) / radius;
            result.obj = this;

            return result;
        }

        return result;
    }
private:
    Vec3 center;
    float radius;
    Vec3 color;
};


//Returns Vec3 of alpha, u, v
// u and v are barycentric coords
Vec3 traceTriangle(Vec3 v0, Vec3 v1, Vec3 v2, Ray ray)
{
    Mat3 matrix;
    matrix.col(0) << -ray.direction;
    matrix.col(1) << v1 - v0;
    matrix.col(2) << v2 - v0;
    Vec3 b = ray.origin - v0;

    Vec3 x = matrix.fullPivLu().solve(b);

    double relative_error = (matrix * x - b).norm() / b.norm();

    if (relative_error < 0.001 && x[0] > 0 && x[1] > 0 && x[2] > 0) // Zero is ignored
    {
        return x;
    }
    else
    {
        return Vec3(-1, -1, -1);
    }
}

void test_triangle()
{
    Ray ray{Vec3(-1, 5, -1), Vec3(0, 1, 0)};
    Vec3 result = traceTriangle(Vec3(0, 0, 0), Vec3(0, 0, 5), Vec3(5, 0, 0), ray);

    std::cout << "Result: " << std::endl << result<< std::endl;

    std::cout << "Intersection: " << ray.origin + result.x() * ray.direction << std::endl;
}

class ExternalModel : public Object
{
public:
    ExternalModel(const std::string &obj_filename);

    TracingResult Trace(const Ray &r) {
        return TracingResult();
    }

private:
    Mat3 rotation;
    Vec3 translation;
};
