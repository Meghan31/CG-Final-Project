// Written by Megha

// Later will be using Utils to Change it into a closed terrain

// Ground plane: just a big green quad at y=0 that everything sits on.
#include "Land.h"
#include <vector>
#include <glm/glm.hpp>
using namespace std;

Mesh createGround() {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    float size = 75.0f; // scene half-size (so the full ground is 150x150)

    // 4 corner vertices of the quad
    vertices.push_back({ glm::vec3(-size, 0.0f, -size), glm::vec3(0.5f, 0.7f, 0.3f) }); // Grass green
    vertices.push_back({ glm::vec3(size, 0.0f, -size), glm::vec3(0.5f, 0.7f, 0.3f) });
    vertices.push_back({ glm::vec3(size, 0.0f, size), glm::vec3(0.5f, 0.7f, 0.3f) });
    vertices.push_back({ glm::vec3(-size, 0.0f, size), glm::vec3(0.5f, 0.7f, 0.3f) });

    // two triangles that make the quad
    indices = { 0, 1, 2, 0, 2, 3 };

    return Mesh(vertices, indices);
}