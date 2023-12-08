#pragma once

#include "image.h"
#include <vector>
#include <string>

bool inCircle(Real x, Real y, Vector2 center, Real radius);
bool inRectangle(Real x, Real y, Vector2 p_min, Vector2 p_max);
bool halfPlane (Vector2 p0, Vector2 p1, Vector2 q);
bool inTriangle(Real x, Real y, Vector2 p0, Vector2 p1, Vector2 p2);



void paintCanvas(Image3* imgPtr,Real width, Real height, Vector3 color);



Image3 hw_1_1(const std::vector<std::string> &params);
Image3 hw_1_2(const std::vector<std::string> &params);
Image3 hw_1_3(const std::vector<std::string> &params);
Image3 hw_1_4(const std::vector<std::string> &params);
Image3 hw_1_5(const std::vector<std::string> &params);
Image3 hw_1_6(const std::vector<std::string> &params);
