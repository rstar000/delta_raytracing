#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "geom.hpp"
Vec3 sample_mirror(Vec3 ivec , Vec3 normal);
Vec3 sample_diffuse(Vec3 ivec, Vec3 normal);

#endif // MATERIAL_HPP
