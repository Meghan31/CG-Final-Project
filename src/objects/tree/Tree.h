// Tree factory functions. One makes a default tree, the other lets me tweak size/colors.
#pragma once
#include "../../rendering/mesh/Mesh.h"
#include <glm/glm.hpp>

Mesh createTree();
Mesh createTreeVariant(float heightScale, float foliageScale, const glm::vec3& leafColor);