#pragma once

#include "balboa.h"
#include "matrix.h"
#include "vector.h"
#include <vector>

namespace hw2 {

struct TriangleMesh {
    std::vector<Vector3> vertices; // 3D positions of the vertices
    std::vector<Vector3i> faces; // indices of the triangles
    std::vector<Vector3> face_colors; // per-face color of the mesh, only used in HW 2.2
    std::vector<Vector3> vertex_colors; // per-vertex color of the mesh, used in HW 2.3 and later
    Matrix4x4 model_matrix;
};

extern std::vector<TriangleMesh> meshes;

struct Camera {
    Matrix4x4 view_matrix;
    Vector2i resolution;
    Real s;
    Real z_near;
};

struct Scene {
    Camera camera;
    Vector3 background;
    std::vector<TriangleMesh> meshes;
};

Scene parse_scene(const fs::path &filename);

std::ostream& operator<<(std::ostream &os, const Camera &camera);
std::ostream& operator<<(std::ostream &os, const TriangleMesh &mesh);
std::ostream& operator<<(std::ostream &os, const Scene &scene);

} // namespace hw2
