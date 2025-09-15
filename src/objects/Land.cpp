#include "Land.h"
#include <vector>
#include <glm/glm.hpp>

Mesh createGround() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float size = 20.0f;

    // vertices
    vertices.push_back({ glm::vec3(-size, 0.0f, -size), glm::vec3(0.6f, 0.6f, 0.6f) });
    vertices.push_back({ glm::vec3(size, 0.0f, -size), glm::vec3(0.6f, 0.6f, 0.6f) });
    vertices.push_back({ glm::vec3(size, 0.0f, size), glm::vec3(0.6f, 0.6f, 0.6f) });
    vertices.push_back({ glm::vec3(-size, 0.0f, size), glm::vec3(0.6f, 0.6f, 0.6f) });

    // indices
    indices = { 0, 1, 2, 0, 2, 3 };

    return Mesh(vertices, indices);
}
