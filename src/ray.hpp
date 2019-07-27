#pragma once

#include <optional>
#include <Eigen/Dense>

using Vec3 = Eigen::Vector3f;

struct Ray
{
    Vec3 origin;
    Vec3 direction;
};

/**
 * Compute reflected ray direction. Don't flip the incident ray direction!
 * @param iray - incident ray
 * @param normal - surface normal
 */
inline Vec3 reflect_ray(const Ray &iray, const Vec3 normal)
{
    
    return Vec3();
}
