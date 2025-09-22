#pragma once

#include "balboa.h"
#include "vector.h"
#include "matrix.h"
#include <variant>
#include <vector>

namespace hw1 {

struct Circle {
    Vector2 center;
    Real radius;
    std::optional<Vector3> fill_color;
    Real fill_alpha;
    std::optional<Vector3> stroke_color;
    Real stroke_alpha;
    Real stroke_width;
    Matrix3x3 transform;
};

struct Polyline {
    std::vector<Vector2> points;
    bool is_closed;
    std::optional<Vector3> fill_color;
    Real fill_alpha;
    std::optional<Vector3> stroke_color;
    Real stroke_alpha;
    Real stroke_width;
    Matrix3x3 transform;
};

using Shape = std::variant<Circle, Polyline>;

inline void set_fill_color(Shape &shape, const Vector3 &fill_color) {
    std::visit([&](auto &s) { s.fill_color = fill_color; }, shape);
}
inline std::optional<Vector3> get_fill_color(const Shape &shape) {
    return std::visit([](const auto &s) { return s.fill_color; }, shape);
}
inline void set_fill_alpha(Shape &shape, Real fill_alpha) {
    std::visit([&](auto &s) { s.fill_alpha = fill_alpha; }, shape);
}
inline Real get_fill_alpha(const Shape &shape) {
    return std::visit([](const auto &s) { return s.fill_alpha; }, shape);
}
inline void set_stroke_color(Shape &shape, const Vector3 &stroke_color) {
    std::visit([&](auto &s) { s.stroke_color = stroke_color; }, shape);
}
inline std::optional<Vector3> get_stroke_color(const Shape &shape) {
    return std::visit([](const auto &s) { return s.stroke_color; }, shape);
}
inline void set_stroke_alpha(Shape &shape, Real stroke_alpha) {
    std::visit([&](auto &s) { s.stroke_alpha = stroke_alpha; }, shape);
}
inline Real get_stroke_alpha(const Shape &shape) {
    return std::visit([](const auto &s) { return s.stroke_alpha; }, shape);
}
inline void set_stroke_width(Shape &shape, Real stroke_width) {
    std::visit([&](auto &s) { s.stroke_width = stroke_width; }, shape);
}
inline Real get_stroke_width(const Shape &shape) {
    return std::visit([](const auto &s) { return s.stroke_width; }, shape);
}
inline void set_transform(Shape &shape, const Matrix3x3 &transform) {
    std::visit([&](auto &s) { s.transform = transform; }, shape);
}
inline Matrix3x3 get_transform(const Shape &shape) {
    return std::visit([](const auto &s) { return s.transform; }, shape);
}

struct Scene {
    Vector2i resolution;
    Vector3 background;
    std::vector<Shape> shapes;
};

Scene parse_scene(const fs::path &filename);

std::ostream& operator<<(std::ostream &os, const Shape &shape);
std::ostream& operator<<(std::ostream &os, const Scene &scene);

} // namespace hw1
