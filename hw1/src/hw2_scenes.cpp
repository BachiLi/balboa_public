#include "hw2_scenes.h"
#include "3rdparty/json.hpp"
#include "3rdparty/tinyply.h"
#include "flexception.h"
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
    {{-0.483444, 0.826069, -2.307457},
     {1.152029, -1.111880, -1.928058},
     {1.485437, 0.880605, -2.239198},
     {0.594299, 0.143237, -1.466344}},
    // faces
    {{0, 1, 2},
     {0, 1, 3},
     {0, 2, 3},
     {1, 2, 3}},
    // face_colors
    {{0.35, 0.75, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}, {0.75, 0.35, 0.75}},
    // vertex_colors
    {{0.75, 0.35, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}, {0.75, 0.35, 0.75}}
};

// Cube
TriangleMesh mesh2 {
    // vertices
    {{-0.492931, 0.128937, -10.741019},
     {0.025111, -1.847709, -9.584261},
     {-1.253942, -1.113622, -7.757049},
     {-1.771980, 0.863028, -8.913807},
     {0.645860, -0.080392, -6.842286},
     {0.127818, 1.896260, -7.999044},
     {1.924910, -0.814484, -8.669510},
     {1.406871, 1.162166, -9.826268}
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

TriangleMesh parse_ply(const fs::path &filename) {
    std::ifstream ifs(filename);
    tinyply::PlyFile ply_file;
    ply_file.parse_header(ifs);

    std::shared_ptr<tinyply::PlyData> vertices, faces, vertex_colors;
    try {
        vertices = ply_file.request_properties_from_element("vertex", { "x", "y", "z" }); 
    } catch (const std::exception & e) { 
        Error(std::string("Vertex positions not found in ") + filename.string());
    }
    try {
        faces = ply_file.request_properties_from_element("face", { "vertex_indices" }); 
    } catch (const std::exception & e) { 
        Error(std::string("Vertex indices not found in ") + filename.string());
    }
    try {
        vertex_colors = ply_file.request_properties_from_element("vertex", { "red", "green", "blue" });
    } catch (const std::exception & e) {
        Error(std::string("Vertex colors not found in ") + filename.string());
    }
    assert(vertices->count == vertex_colors->count);

    ply_file.read(ifs);

    TriangleMesh mesh;
    mesh.vertices.resize(vertices->count);
    if (vertices->t == tinyply::Type::FLOAT32) {
        float *data = (float*)vertices->buffer.get();
        for (size_t i = 0; i < vertices->count; i++) {
            mesh.vertices[i] = Vector3{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (vertices->t == tinyply::Type::FLOAT64) {
        double *data = (double*)vertices->buffer.get();
        for (size_t i = 0; i < vertices->count; i++) {
            mesh.vertices[i] = Vector3{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else {
        Error(std::string("Unknown type of vertex positions in ") + filename.string());
    }

    mesh.vertex_colors.resize(vertex_colors->count);
    if (vertex_colors->t == tinyply::Type::FLOAT32) {
        float *data = (float*)vertex_colors->buffer.get();
        for (size_t i = 0; i < vertex_colors->count; i++) {
            mesh.vertex_colors[i] = Vector3{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (vertex_colors->t == tinyply::Type::FLOAT64) {
        double *data = (double*)vertex_colors->buffer.get();
        for (size_t i = 0; i < vertex_colors->count; i++) {
            mesh.vertex_colors[i] = Vector3{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (vertex_colors->t == tinyply::Type::UINT8) {
        uint8_t *data = (uint8_t*)vertex_colors->buffer.get();
        for (size_t i = 0; i < vertex_colors->count; i++) {
            mesh.vertex_colors[i] = Vector3{
                std::pow(Real(data[3 * i]) / 255, Real(2.2)),
                std::pow(Real(data[3 * i + 1]) / 255, Real(2.2)),
                std::pow(Real(data[3 * i + 2]) / 255, Real(2.2))};
        }
    } else {
        Error(std::string("Unknown type of vertex colors in ") + filename.string());
    }
    
    mesh.faces.resize(faces->count);
    if (faces->t == tinyply::Type::INT8) {
        int8_t *data = (int8_t*)faces->buffer.get();
        for (size_t i = 0; i < faces->count; i++) {
            mesh.faces[i] = Vector3i{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (faces->t == tinyply::Type::UINT8) {
        uint8_t *data = (uint8_t*)faces->buffer.get();
        for (size_t i = 0; i < faces->count; i++) {
            mesh.faces[i] = Vector3i{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (faces->t == tinyply::Type::INT16) {
        int16_t *data = (int16_t*)faces->buffer.get();
        for (size_t i = 0; i < faces->count; i++) {
            mesh.faces[i] = Vector3i{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (faces->t == tinyply::Type::UINT16) {
        uint16_t *data = (uint16_t*)faces->buffer.get();
        for (size_t i = 0; i < faces->count; i++) {
            mesh.faces[i] = Vector3i{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (faces->t == tinyply::Type::INT32) {
        int32_t *data = (int32_t*)faces->buffer.get();
        for (size_t i = 0; i < faces->count; i++) {
            mesh.faces[i] = Vector3i{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else if (faces->t == tinyply::Type::UINT32) {
        uint32_t *data = (uint32_t*)faces->buffer.get();
        for (size_t i = 0; i < faces->count; i++) {
            mesh.faces[i] = Vector3i{
                data[3 * i], data[3 * i + 1], data[3 * i + 2]};
        }
    } else {
        Error(std::string("Unknown type of faces in ") + filename.string());
    }

    return mesh;
}

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
            Vector3 axis = normalize(Vector3{
                (*rotate_it)[1], (*rotate_it)[2], (*rotate_it)[3]
            });
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
                up = normalize(Vector3{
                    (*up_it)[0], (*up_it)[1], (*up_it)[2]
                });
            }
            // TODO (HW2.4): construct a lookat matrix and composite with F
        }
    }
    return F;
}

Scene parse_scene(const fs::path &filename) {
    std::ifstream f(filename.string().c_str());
    json data = json::parse(f);

    // back up the current working directory and switch to the parent folder of the file
    fs::path old_path = fs::current_path();
    fs::current_path(filename.parent_path());

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
    scene.camera.cam_to_world = parse_transformation(*camera);
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
        if (auto fn_it = it->find("filename"); fn_it != it->end()) {
            mesh = parse_ply(std::string(*fn_it));
        } else {
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
        }
        
        mesh.model_matrix = parse_transformation(*it);
        scene.meshes.push_back(mesh);
    }

    // switch back to the old current working directory
    fs::current_path(old_path);
    return scene;
}

std::ostream& operator<<(std::ostream &os, const Camera &camera) {
    os << "Camera[" << std::endl;
    os << "\tcam_to_world=" << std::endl << camera.cam_to_world << std::endl;
    os << "\tresolution=" << camera.resolution << std::endl;
    os << "\ts=" << camera.s << std::endl;
    os << "\tz_near=" << camera.z_near << std::endl;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream &os, const TriangleMesh &mesh) {
    os << "TriangleMesh[" << std::endl;
    os << "\tnum_vertices=" << mesh.vertices.size() << std::endl;
    os << "\tnum_faces=" << mesh.faces.size() << std::endl;
    os << "\ttransform=" << std::endl << mesh.model_matrix << std::endl;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene[" << std::endl;
    os << "\t" << scene.camera << std::endl;
    os << "\tBackground:" << scene.background << std::endl;
    for (auto s : scene.meshes) {
        os << "\t" << s << std::endl;
    }
    os << "]";
    return os;
}

} // namespace hw2
