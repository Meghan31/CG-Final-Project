#pragma once
#include "../rendering/mesh/Mesh.h"  // FIXED: Use relative path
#include <vector>
#include <glm/glm.hpp>

// Helper: build extruded indexed mesh from 2D footprint (x,z) and height with color
Mesh buildExtrudedIndexed(const std::vector<glm::vec3>& footprint, float height, const glm::vec3& color);