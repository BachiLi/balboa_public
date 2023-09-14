#pragma once

#include "balboa.h"
#include "vector.h"
#include <vector>

namespace hw2 {

struct TriangleMesh {
	std::vector<Vector3> vertices; // 3D positions of the vertices
	std::vector<Vector3i> faces; // indices of the triangles
	std::vector<Vector3> face_colors; // per-face color of the mesh, only used in HW 2.2
};

// Two isolated triangles
TriangleMesh mesh0 {
	{{-1.7, 1.0, -5.0}, {1.0, 1.0, -5.0}, {-0.5, -1.0, -5.0},
     {-1.0, 1.5, -4.0}, {0.2, 1.5, -4.0}, { 0.2, -1.5, -4.0}}, 
    {{0, 1, 2}, {3, 4, 5}},
    {{0.35, 0.75, 0.35}, {0.35, 0.35, 0.75}}
};

std::vector<TriangleMesh> meshes = {mesh0};

}

