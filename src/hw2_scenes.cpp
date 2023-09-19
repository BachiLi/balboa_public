#include "hw2_scenes.h"
#include "3rdparty/json.hpp"
#include "flexception.h"
#include "matrix.h"
#include <fstream>

using json = nlohmann::json;

namespace hw2 {

// A triangle and a quadliteral
TriangleMesh mesh0 {
    // vertices
    {{-1.7, 1.0, -5.0}, {1.0, 1.0, -5.0}, {-0.5, -1.0, -5.0}, {-2.5, -1.0, -5.0},
     {-1.0, 1.5, -4.0}, {0.2, 1.5, -4.0}, { 0.2, -1.5, -4.0}},
    // faces
    {{0, 1, 2}, {0, 2, 3}, {4, 5, 6}},
    // face_colors
    {{0.35, 0.75, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}},
    // vertex_colors
    {{0.75, 0.35, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}, {0.75, 0.35, 0.75},
     {0.35, 0.75, 0.75}, {0.75, 0.35, 0.75}, {0.75, 0.75, 0.35}}
};

// Tetrahedron
TriangleMesh mesh1 {
    // vertices
    {{-4.0, 0.0, -5.0}, {0.0, 2.0, -5.0}, {1.5, -2.3, -3.0}, {-1.0, 0.0, -5.0}},
    // faces
    {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}},
    // face_colors
    {{0.35, 0.75, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}, {0.75, 0.35, 0.75}},
    // vertex_colors
    {{0.75, 0.35, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}, {0.75, 0.35, 0.75}}
};

// Cube
TriangleMesh mesh2 {
    // vertices
    {{-0.492931, 0.128937, -24.255093},
     {0.025111, -1.847709, -23.098335},
     {-1.253942, -1.113622, -21.271122},
     {-1.771980, 0.863028, -22.427881},
     {0.645860, -0.080392, -20.356359},
     {0.127818, 1.896260, -21.513117},
     {1.924910, -0.814484, -22.183584},
     {1.406871, 1.162166, -23.340342}
    },
    // faces
    {{0, 1, 2}, {0, 2, 3},
     {3, 2, 4}, {3, 4, 5},
     {5, 4, 6}, {5, 6, 7},
     {7, 6, 1}, {7, 1, 0},
     {3, 5, 7}, {3, 7, 0},
     {4, 2, 1}, {4, 1, 6}
    },
    // face_colors
    {{0.2, 0.5, 0.8}, {0.2, 0.5, 0.8},
     {0.2, 0.8, 0.5}, {0.2, 0.8, 0.5},
     {0.8, 0.2, 0.5}, {0.8, 0.2, 0.5},
     {0.8, 0.8, 0.2}, {0.8, 0.8, 0.2},
     {0.2, 0.8, 0.8}, {0.2, 0.8, 0.8},
     {0.8, 0.2, 0.8}, {0.8, 0.2, 0.8}
    },
    // vertex_colors
    {{0.2, 0.2, 0.2},
     {0.8, 0.2, 0.2},
     {0.2, 0.8, 0.2},
     {0.2, 0.2, 0.8},
     {0.2, 0.8, 0.8},
     {0.8, 0.2, 0.8},
     {0.8, 0.8, 0.2},
     {0.8, 0.8, 0.8}}
};

// Prism
TriangleMesh mesh3 {
    // vertices
    {{-0.424823, -0.659383, -1.59265},
     {0.407141, 1.11459, -1.99373},
     {0.93389, -1.5588, -2.75237},
     {-0.951021, -0.568008, -2.28},
     {-0.119057, 1.20596, -2.68108},
     {0.407693, -1.46742, -3.43972}
    },
    // faces
    {{0, 1, 2},
     {0, 1, 3}, {1, 3, 4},
     {0, 3, 2}, {3, 2, 5},
     {3, 4, 5},
     {1, 2, 4}, {2, 4, 5}
    },
    // face_colors
    {{0.9, 0.1, 0.5},
     {0.3, 0.8, 0.3}, {0.3, 0.8, 0.3},
     {0.8, 0.8, 0.3}, {0.8, 0.8, 0.3},
     {0.1, 0.9, 0.5},
     {0.3, 0.8, 0.8}, {0.3, 0.8, 0.8},
    },
    // vertex_colors
    {{0.8, 0.2, 0.2},
     {0.2, 0.8, 0.2},
     {0.2, 0.2, 0.8},
     {0.2, 0.8, 0.8},
     {0.8, 0.2, 0.8},
     {0.8, 0.8, 0.2}}
};

std::vector<TriangleMesh> meshes = {mesh0, mesh1, mesh2, mesh3};

Matrix4x4 parse_transformation(const json &node) {
    // Homework 2.4: parse a sequence of linear transformation and 
    // combine them into a 4x4 transformation matrix
    Matrix4x4 F = Matrix4x4::identity();
    auto transform_it = node.find("transform");
    if (transform_it == node.end()) {
        // Transformation not specified, return identity.
        return F;
    }

    for (auto it = transform_it->begin(); it != transform_it->end(); it++) {
        if (auto scale_it = it->find("scale"); scale_it != it->end()) {
            Vector3 scale = Vector3{
                (*scale_it)[0], (*scale_it)[1], (*scale_it)[2]
            };
            // TODO (HW2.4): construct a scale matrix and composite with F
            UNUSED(scale); // silence warning, feel free to remove it
        } else if (auto rotate_it = it->find("rotate"); rotate_it != it->end()) {
            Real angle = (*rotate_it)[0];
            Vector3 axis = Vector3{
                (*rotate_it)[0], (*rotate_it)[1], (*rotate_it)[2]
            };
            // TODO (HW2.4): construct a rotation matrix and composite with F
            UNUSED(angle); // silence warning, feel free to remove it
            UNUSED(axis); // silence warning, feel free to remove it
        } else if (auto translate_it = it->find("translate"); translate_it != it->end()) {
            Vector3 translate = Vector3{
                (*translate_it)[0], (*translate_it)[1], (*translate_it)[2]
            };
            // TODO (HW2.4): construct a translation matrix and composite with F
            UNUSED(translate); // silence warning, feel free to remove it
        } else if (auto lookat_it = it->find("lookat"); lookat_it != it->end()) {
            Vector3 position{0, 0, 0};
            Vector3 target{0, 0, -1};
            Vector3 up{0, 1, 0};
            auto position_it = lookat_it->find("position");
            auto target_it = lookat_it->find("target");
            auto up_it = lookat_it->find("up");
            if (position_it != lookat_it->end()) {
                position = Vector3{
                    (*position_it)[0], (*position_it)[1], (*position_it)[2]
                };
            }
            if (target_it != lookat_it->end()) {
                target = Vector3{
                    (*target_it)[0], (*target_it)[1], (*target_it)[2]
                };
            }
            if (up_it != lookat_it->end()) {
                up = Vector3{
                    (*up_it)[0], (*up_it)[1], (*up_it)[2]
                };
            }
            // TODO (HW2.4): construct a lookat matrix and composite with F
        }
    }
    return F;
}

Scene parse_scene(const fs::path &filename) {
    std::ifstream f(filename.string().c_str());
    json data = json::parse(f);
    Scene scene;
    
    auto camera = data.find("camera");
    if (camera == data.end()) {
        Error("Scene does not contain the field \"camera\".");
        return scene;        
    }

    auto res = camera->find("resolution");
    if (res == camera->end()) {
        Error("Camera does not contain the field \"resolution\".");
        return scene;
    }
    scene.camera.resolution = Vector2i{(*res)[0], (*res)[1]};
    scene.camera.view_matrix = inverse(parse_transformation(*camera));
    scene.camera.s = 1;
    if (auto s = camera->find("s"); s != camera->end()) {
        scene.camera.s = *s;
    }
    scene.camera.z_near = Real(1e-6);
    if (auto z_near = camera->find("z_near"); z_near != camera->end()) {
        scene.camera.z_near = *z_near;
    }

    auto background = data.find("background");
    scene.background = Vector3{1, 1, 1};
    if (background != data.end()) {
        scene.background = Vector3{
            (*background)[0], (*background)[1], (*background)[2]
        };
    }

    auto objects = data.find("objects");
    for (auto it = objects->begin(); it != objects->end(); it++) {
        TriangleMesh mesh;

        auto vertices_it = it->find("vertices");
        if (vertices_it != it->end()) {
            int num_vertices = vertices_it->size() / 3;
            mesh.vertices.resize(num_vertices);
            for (int i = 0; i < num_vertices; i++) {
                mesh.vertices[i] = Vector3{
                    (*vertices_it)[3 * i + 0],
                    (*vertices_it)[3 * i + 1],
                    (*vertices_it)[3 * i + 2]
                };
            }
        }
        auto faces_it = it->find("faces");
        if (faces_it != it->end()) {
            int num_triangles = faces_it->size() / 3;
            mesh.faces.resize(num_triangles);
            for (int i = 0; i < num_triangles; i++) {
                mesh.faces[i] = Vector3i{
                    (*faces_it)[3 * i + 0],
                    (*faces_it)[3 * i + 1],
                    (*faces_it)[3 * i + 2]
                };
            }
        }
        auto vertex_colors_it = it->find("vertex_colors");
        if (vertex_colors_it != it->end()) {
            int num_vertices = vertex_colors_it->size() / 3;
            mesh.vertex_colors.resize(num_vertices);
            if (mesh.vertex_colors.size() != mesh.vertices.size()) {
                Error("Mesh has different number of vertices and number of colors.");
                return scene;
            }
            for (int i = 0; i < num_vertices; i++) {
                mesh.vertex_colors[i] = Vector3{
                    (*vertex_colors_it)[3 * i + 0],
                    (*vertex_colors_it)[3 * i + 1],
                    (*vertex_colors_it)[3 * i + 2]
                };
            }
        }

        mesh.model_matrix = parse_transformation(*it);
        scene.meshes.push_back(mesh);
    }

    return scene;
}

std::ostream& operator<<(std::ostream &os, const Camera &camera) {
    os << "Camera[";
    os << "\tview_matrix=" << std::endl << camera.view_matrix << std::endl;
    os << "\tresolution=" << camera.resolution << std::endl;
    os << "\ts=" << camera.s << std::endl;
    os << "\tz_near=" << camera.z_near << std::endl;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream &os, const TriangleMesh &mesh) {
    os << "TriangleMesh[";
    os << "\tnum_vertices=" << mesh.vertices.size() << std::endl;
    os << "\tnum_faces=" << mesh.faces.size() << std::endl;
    os << "\ttransform=" << std::endl << mesh.model_matrix << std::endl;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene[";
    os << "\t" << scene.camera << std::endl;
    os << "\tBackground:" << scene.background << std::endl;
    for (auto s : scene.meshes) {
        os << "\t" << s << std::endl;
    }
    os << "]";
    return os;
}

} // namespace hw2
