#include "Land.h"
#include <vector>
#include <glm/glm.hpp>
using namespace std;

Mesh createGround() {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    float size = 75.0f; // Increased size for larger scene

    // vertices
    vertices.push_back({ glm::vec3(-size, 0.0f, -size), glm::vec3(0.5f, 0.7f, 0.3f) }); // Grass green
    vertices.push_back({ glm::vec3(size, 0.0f, -size), glm::vec3(0.5f, 0.7f, 0.3f) });
    vertices.push_back({ glm::vec3(size, 0.0f, size), glm::vec3(0.5f, 0.7f, 0.3f) });
    vertices.push_back({ glm::vec3(-size, 0.0f, size), glm::vec3(0.5f, 0.7f, 0.3f) });

    // indices
    indices = { 0, 1, 2, 0, 2, 3 };

    return Mesh(vertices, indices);
}