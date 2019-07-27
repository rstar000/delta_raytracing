#pragma once

#include <cmath>

#include "geom.hpp"

class BRDF
{
public:
    BRDF() = default;
    
    virtual float Density(const Vec3 &ivec, const Vec3 &normal) = 0;
};


class Diffuse : public BRDF
{
    float Density(const Vec3 &ivec, const Vec3 &normal)
    {
        return 1.0f / M_PI;
    } 
};