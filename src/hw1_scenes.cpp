#include "hw1_scenes.h"
#include "3rdparty/json.hpp"
#include "flexception.h"
#include "matrix.h"
#include <fstream>

using json = nlohmann::json;

namespace hw1 {

Matrix3x3 parse_transformation(const json &node) {
    // Homework 1.4: parse a sequence of linear transformation and 
    // combine them into an affine matrix
    Matrix3x3 F = Matrix3x3::identity();
    auto transform_it = node.find("transform");
    if (transform_it == node.end()) {
        // Transformation not specified, return identity.
        return F;
    }

    for (auto it = transform_it->begin(); it != transform_it->end(); it++) {
        if (auto scale_it = it->find("scale"); scale_it != it->end()) {
            Vector2 scale = Vector2{
                (*scale_it)[0], (*scale_it)[1]
            };
            // TODO (HW1.4): construct a scale matrix and composite with F
            UNUSED(scale); // silence warning, feel free to remove it
        } else if (auto rotate_it = it->find("rotate"); rotate_it != it->end()) {
            Real angle = *rotate_it;
            // TODO (HW1.4): construct a rotation matrix and composite with F
            UNUSED(angle); // silence warning, feel free to remove it
        } else if (auto translate_it = it->find("translate"); translate_it != it->end()) {
            Vector2 translate = Vector2{
                (*translate_it)[0], (*translate_it)[1]
            };
            // TODO (HW1.4): construct a translation matrix and composite with F
            UNUSED(translate); // silence warning, feel free to remove it
        } else if (auto shearx_it = it->find("shear_x"); shearx_it != it->end()) {
            Real shear_x = *shearx_it;
            // TODO (HW1.4): construct a shear matrix (x direction) and composite with F
            UNUSED(shear_x); // silence warning, feel free to remove it
        } else if (auto sheary_it = it->find("shear_y"); sheary_it != it->end()) {
            Real shear_y = *sheary_it;
            // TODO (HW1.4): construct a shear matrix (y direction) and composite with F
            UNUSED(shear_y); // silence warning, feel free to remove it
        }
    }
    return F;
}

Scene parse_scene(const fs::path &filename) {
    std::ifstream f(filename.string().c_str());
    json data = json::parse(f);
    Scene scene;
    
    auto res = data.find("resolution");
    if (res == data.end()) {
        Error("Scene does not contain the field \"resolution\".");
        return scene;
    }
    scene.resolution = Vector2i{(*res)[0], (*res)[1]};
    
    auto background = data.find("background");
    scene.background = Vector3{1, 1, 1};
    if (background != data.end()) {
        scene.background = Vector3{
            (*background)[0], (*background)[1], (*background)[2]
        };
    }

    auto objects = data.find("objects");
    for (auto it = objects->begin(); it != objects->end(); it++) {
        if (it->find("type") == it->end()) {
            Error("Object with undefined type.");
        }
        if ((*it)["type"] == "circle") {
            Circle circle;
            circle.center = Vector2{0, 0};
            circle.radius = 1;
            circle.fill_alpha = 1;
            circle.stroke_alpha = 1;
            circle.stroke_width = 1;

            auto center_it = it->find("center");
            if (center_it != it->end()) {
                circle.center = Vector2{
                    (*center_it)[0], (*center_it)[1]
                };
            }
            auto radius_it = it->find("radius");
            if (radius_it != it->end()) {
                circle.radius = (*radius_it);
            }
            auto fill_color_it = it->find("fill_color");
            if (fill_color_it != it->end()) {
                circle.fill_color = Vector3{
                    (*fill_color_it)[0], (*fill_color_it)[1], (*fill_color_it)[2]
                };
            }
            auto fill_alpha_it = it->find("fill_alpha");
            if (fill_alpha_it != it->end()) {
                circle.fill_alpha = (*fill_alpha_it);
            }
            auto stroke_color_it = it->find("stroke_color");
            if (stroke_color_it != it->end()) {
                circle.stroke_color = Vector3{
                    (*stroke_color_it)[0], (*stroke_color_it)[1], (*stroke_color_it)[2]
                };
            }
            auto stroke_alpha_it = it->find("stroke_alpha");
            if (stroke_alpha_it != it->end()) {
                circle.stroke_alpha = (*stroke_alpha_it);
            }
            auto stroke_width_it = it->find("stroke_width");
            if (stroke_width_it != it->end()) {
                circle.stroke_width = (*stroke_width_it);
            }
            circle.transform = parse_transformation(*it);
            scene.shapes.push_back(circle);
        } else if ((*it)["type"] == "polyline") {
            Polyline polyline;
            polyline.is_closed = true;
            polyline.fill_alpha = 1;
            polyline.stroke_alpha = 1;
            polyline.stroke_width = 1;

            auto points_it = it->find("points");
            if (points_it != it->end()) {
                for (int i = 0; i < (int)points_it->size() / 2; i++) {
                    Real x = (*points_it)[2 * i];
                    Real y = (*points_it)[2 * i + 1];
                    polyline.points.push_back(Vector2{x, y});
                }
            }
            auto is_closed_it = it->find("is_closed");
            if (is_closed_it != it->end()) {
                polyline.is_closed = *is_closed_it;
            }
            auto fill_color_it = it->find("fill_color");
            if (fill_color_it != it->end()) {
                polyline.fill_color = Vector3{
                    (*fill_color_it)[0], (*fill_color_it)[1], (*fill_color_it)[2]
                };
            }
            auto fill_alpha_it = it->find("fill_alpha");
            if (fill_alpha_it != it->end()) {
                polyline.fill_alpha = (*fill_alpha_it);
            }
            auto stroke_color_it = it->find("stroke_color");
            if (stroke_color_it != it->end()) {
                polyline.stroke_color = Vector3{
                    (*stroke_color_it)[0], (*stroke_color_it)[1], (*stroke_color_it)[2]
                };
            }
            auto stroke_alpha_it = it->find("stroke_alpha");
            if (stroke_alpha_it != it->end()) {
                polyline.stroke_alpha = (*stroke_alpha_it);
            }
            auto stroke_width_it = it->find("stroke_width");
            if (stroke_width_it != it->end()) {
                polyline.stroke_width = (*stroke_width_it);
            }
            polyline.transform = parse_transformation(*it);
            scene.shapes.push_back(polyline);
        } else if ((*it)["type"] == "rectangle") {
            Polyline polyline;
            polyline.is_closed = true;
            polyline.fill_alpha = 1;
            polyline.stroke_alpha = 1;
            polyline.stroke_width = 1;
            Vector2 p_min{0, 0};
            Vector2 p_max{1, 1};

            auto p_min_it = it->find("p_min");
            if (p_min_it != it->end()) {
                p_min = Vector2{
                    (*p_min_it)[0], (*p_min_it)[1]
                };
            }
            auto p_max_it = it->find("p_max");
            if (p_max_it != it->end()) {
                p_max = Vector2{
                    (*p_max_it)[0], (*p_max_it)[1]
                };
            }
            polyline.points.push_back(p_min);
            polyline.points.push_back(Vector2{p_min.x, p_max.y});
            polyline.points.push_back(p_max);
            polyline.points.push_back(Vector2{p_max.x, p_min.y});
            auto fill_color_it = it->find("fill_color");
            if (fill_color_it != it->end()) {
                polyline.fill_color = Vector3{
                    (*fill_color_it)[0], (*fill_color_it)[1], (*fill_color_it)[2]
                };
            }
            auto fill_alpha_it = it->find("fill_alpha");
            if (fill_alpha_it != it->end()) {
                polyline.fill_alpha = (*fill_alpha_it);
            }
            auto stroke_color_it = it->find("stroke_color");
            if (stroke_color_it != it->end()) {
                polyline.stroke_color = Vector3{
                    (*stroke_color_it)[0], (*stroke_color_it)[1], (*stroke_color_it)[2]
                };
            }
            auto stroke_alpha_it = it->find("stroke_alpha");
            if (stroke_alpha_it != it->end()) {
                polyline.stroke_alpha = (*stroke_alpha_it);
            }
            auto stroke_width_it = it->find("stroke_width");
            if (stroke_width_it != it->end()) {
                polyline.stroke_width = (*stroke_width_it);
            }
            polyline.transform = parse_transformation(*it);
            scene.shapes.push_back(polyline);
        } else if ((*it)["type"] == "triangle") {
            Polyline polyline;
            polyline.is_closed = true;
            polyline.fill_alpha = 1;
            polyline.stroke_alpha = 1;
            polyline.stroke_width = 1;
            Vector2 p0{0, 0};
            Vector2 p1{1, 0};
            Vector2 p2{0, 1};

            auto p0_it = it->find("p0");
            if (p0_it != it->end()) {
                p0 = Vector2{
                    (*p0_it)[0], (*p0_it)[1]
                };
            }
            auto p1_it = it->find("p1");
            if (p1_it != it->end()) {
                p1 = Vector2{
                    (*p1_it)[0], (*p1_it)[1]
                };
            }
            auto p2_it = it->find("p2");
            if (p2_it != it->end()) {
                p2 = Vector2{
                    (*p2_it)[0], (*p2_it)[1]
                };
            }
            polyline.points.push_back(p0);
            polyline.points.push_back(p1);
            polyline.points.push_back(p2);
            auto fill_color_it = it->find("fill_color");
            if (fill_color_it != it->end()) {
                polyline.fill_color = Vector3{
                    (*fill_color_it)[0], (*fill_color_it)[1], (*fill_color_it)[2]
                };
            }
            auto fill_alpha_it = it->find("fill_alpha");
            if (fill_alpha_it != it->end()) {
                polyline.fill_alpha = (*fill_alpha_it);
            }
            auto stroke_color_it = it->find("stroke_color");
            if (stroke_color_it != it->end()) {
                polyline.stroke_color = Vector3{
                    (*stroke_color_it)[0], (*stroke_color_it)[1], (*stroke_color_it)[2]
                };
            }
            auto stroke_alpha_it = it->find("stroke_alpha");
            if (stroke_alpha_it != it->end()) {
                polyline.stroke_alpha = (*stroke_alpha_it);
            }
            auto stroke_width_it = it->find("stroke_width");
            if (stroke_width_it != it->end()) {
                polyline.stroke_width = (*stroke_width_it);
            }
            polyline.transform = parse_transformation(*it);
            scene.shapes.push_back(polyline);
        }
    }

    return scene;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::optional<T> &x) {
    if (x) {
        os << *x;
    } else {
        os << "None";    
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const Shape &shape) {
    os << "Shape[type=";
    if (auto *circle = std::get_if<Circle>(&shape)) {
        os << "Circle, " << 
              "center=" << circle->center << ", " <<
              "radius=" << circle->radius << ", " <<
              "fill_color=" << circle->fill_color << ", " <<
              "fill_alpha=" << circle->fill_alpha << ", " <<
              "stroke_color=" << circle->stroke_color << ", " <<
              "stroke_alpha=" << circle->stroke_alpha << ", " <<
              "stroke_width=" << circle->stroke_width << ", " <<
              "transform=" << std::endl << circle->transform << "]";
    } else if (auto *polyline = std::get_if<Polyline>(&shape)) {
        os << "Polyline, points=[";
        bool first = true;
        for (auto it : polyline->points) {
            if (!first) os << ", ";
            os << it;
            first = false;
        }
        os << "], ";
        os << "is_closed=" << polyline->is_closed << ", " <<
              "fill_color=" << polyline->fill_color << ", " << 
              "fill_alpha=" << polyline->fill_alpha << ", " << 
              "stroke_color=" << polyline->stroke_color << ", " << 
              "stroke_alpha=" << polyline->stroke_alpha << ", " << 
              "stroke_width=" << polyline->stroke_width << ", " <<
              "transform=" << std::endl << polyline->transform << "]";
    } else {
        // Likely an unhandled case.
        os << "Unknown]";
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene[";
    os << "Resolution:" << scene.resolution << std::endl;
    os << "\tBackground:" << scene.background << std::endl;
    for (auto s : scene.shapes) {
        os << "\t" << s << std::endl;
    }
    os << "]";
    return os;
}

} // namespace hw1
