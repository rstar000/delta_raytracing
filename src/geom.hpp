// Geometric utility functions
#pragma once

#include <Eigen/Dense>

using Vec3 = Eigen::Vector3f;
using Vec4 = Eigen::Vector4f;
using Mat3 = Eigen::Matrix3f;
using Mat4 = Eigen::Matrix4f;

/* Construct an orthonormal system from one vector. */
Mat3 construct_ons(Vec3 x);

Vec3 sample_hemi_uniform(float u1, float u2);

Vec3 sample_hemi_cosine(float u1, float u2);

Mat3 camera_basis(Vec3 origin, Vec3 look_at);

Vec3 sample_hemi_weighted(float u1, float u2, float m);