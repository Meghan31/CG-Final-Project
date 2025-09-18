// Helpers for building meshes.
#pragma once
#include "../rendering/mesh/Mesh.h"  // relative path into Mesh
#include <vector>
#include <glm/glm.hpp>

// Build a prism by extruding a 2D footprint up to a height (all one color)
Mesh buildExtrudedIndexed(const std::vector<glm::vec3>& footprint, float height, const glm::vec3& color);