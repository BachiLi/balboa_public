#pragma once

#include "image.h"
#include "hw1.h"
#include <vector>
#include <string>

Image3 hw_2_1(const std::vector<std::string> &params);
Image3 hw_2_2(const std::vector<std::string> &params);
Image3 hw_2_3(const std::vector<std::string> &params);
Image3 hw_2_4(const std::vector<std::string> &params);

void paintCanvas(Image3* imgPtr, Vector3 color);
Vector2 c_space_to_i_space(Vector2 v, Real s, Real a, Real width, Real height);
Vector2 projectedPoint(Vector3 v);
Vector3 projectedPoint_v3(Vector3 v);
Vector3 projected_barycentric_coordinate(Vector3 b_prime, Vector3 vector_zs, Vector3 p0p, Vector3 p1p, Vector3 p2p);
Vector3 unique_coefficient(Vector3 p0p, Vector3 p1p, Vector3 p2p, Vector3 p);
Real original_depth(Vector3 b, Vector3 p0, Vector3 p1, Vector3 p2);
Vector3 original_coefficients(Vector3 b_prime, Vector3 p0, Vector3 p1, Vector3 p2);
Real depth_in_world(Vector2 pp, Vector3 p0, Vector3 p1, Vector3 p2, Real s, Real width, Real height);
Vector2 c_space_to_i_space(Vector2 v, Real s, Real width, Real height);
std::vector<Vector2> projected_in_i(Vector3 p0, Vector3 p1, Vector3 p2, Real s, Real width, Real height);
Vector3 vector2_to_3(Vector2 v, Real z);
Vector3 vector4_to_3(Vector4 v);
Vector4 vector3_to_4(Vector3 v, Real w);






