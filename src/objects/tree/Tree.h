#pragma once
#include "../../rendering/mesh/Mesh.h"
#include <glm/glm.hpp>

Mesh createTree();
Mesh createTreeVariant(float heightScale, float foliageScale, const glm::vec3& leafColor);