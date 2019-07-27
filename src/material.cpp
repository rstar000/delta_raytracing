#include "material.hpp"

Vec3 sample_mirror(Vec3 ivec, Vec3 normal)
{
    return (ivec + 2*normal * ivec.dot(normal));
}
