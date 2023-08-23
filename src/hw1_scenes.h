#pragma once

#include "balboa.h"
#include "vector.h"
#include <variant>
#include <vector>

namespace hw1 {

struct Circle {
    Vector2 center;
    Real radius;
    Vector3 color;
};

struct CircleScene {
    Vector2i resolution;
    Vector3 background;
    std::vector<Circle> objects;
};

extern CircleScene hw1_2_scenes[];

struct Rectangle {
    Vector2 p_min, p_max;
    Vector3 color;
};

struct Triangle {
    Vector2 p0, p1, p2;
    Vector3 color;
};

using Shape = std::variant<Circle, Rectangle, Triangle>;

inline void set_color(Shape &shape, const Vector3 &color) {
    std::visit([&](auto &s) { s.color = color; }, shape);
}
inline Vector3 get_color(const Shape &shape) {
    return std::visit([](const auto &s) { return s.color; }, shape);
}

struct Scene {
    Vector2i resolution;
    Vector3 background;
    std::vector<Shape> shapes;
};

Scene parse_scene(const fs::path &filename);

std::ostream& operator<<(std::ostream &os, const Shape &shape);
std::ostream& operator<<(std::ostream &os, const Scene &scene);


}
