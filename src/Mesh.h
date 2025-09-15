#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
};

class Mesh {
public:
    unsigned int VAO, VBO;
    int vertexCount;
    Mesh(const std::vector<Vertex>& vertices);
    void Draw();
};
