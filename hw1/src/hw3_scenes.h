#pragma once

#include "balboa.h"
#include "matrix.h"
#include "vector.h"
#include <vector>

namespace hw3 {

struct TriangleMesh {
    std::vector<Vector3f> vertices; // 3D positions of the vertices
    std::vector<Vector3i> faces; // indices of the triangles
    std::vector<Vector3f> vertex_colors; // per-vertex color of the mesh
    std::vector<Vector2f> uvs; // UV coordinates (for bonus)
    std::vector<Vector3f> vertex_normals; // vertex normals (for lighting in 3.4)
    Matrix4x4f model_matrix;
};

struct Camera {
    Matrix4x4f cam_to_world; // inverse of the view matrix
    Vector2i resolution;
    Real s; // tan(vfov/2)
    Real z_near, z_far;
};

struct Scene {
    Camera camera;
    Vector3f background;
    std::vector<TriangleMesh> meshes;
};

Scene parse_scene(const fs::path &filename);

std::ostream& operator<<(std::ostream &os, const Camera &camera);
std::ostream& operator<<(std::ostream &os, const TriangleMesh &mesh);
std::ostream& operator<<(std::ostream &os, const Scene &scene);

} // namespace hw3
