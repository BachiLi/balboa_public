#pragma once

#include "balboa.h"
#include "vector.h"
#include <vector>

namespace hw2 {

struct TriangleMesh {
    std::vector<Vector3> vertices; // 3D positions of the vertices
    std::vector<Vector3i> faces; // indices of the triangles
    std::vector<Vector3> face_colors; // per-face color of the mesh, only used in HW 2.2
    std::vector<Vector3> vertex_colors; // per-vertex color of the mesh, used in HW 2.3 and later
};

// Two isolated triangles
TriangleMesh mesh0 {
    // vertices
    {{-1.7, 1.0, -5.0}, {1.0, 1.0, -5.0}, {-0.5, -1.0, -5.0},
     {-1.0, 1.5, -4.0}, {0.2, 1.5, -4.0}, { 0.2, -1.5, -4.0}},
    // faces
    {{0, 1, 2}, {3, 4, 5}},
    // face_colors
    {{0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}},
    // vertex_colors
    {{0.75, 0.35, 0.35}, {0.35, 0.75, 0.35}, {0.35, 0.35, 0.75},
     {0.35, 0.75, 0.75}, {0.75, 0.35, 0.75}, {0.75, 0.75, 0.35}}
};

std::vector<TriangleMesh> meshes = {mesh0};

}

