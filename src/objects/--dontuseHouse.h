#pragma once
#include "../Mesh.h"
#include <glm/glm.hpp>

Mesh createHouse();
Mesh createHouseVariant(int type, const glm::vec3& wallColor, const glm::vec3& roofColor);