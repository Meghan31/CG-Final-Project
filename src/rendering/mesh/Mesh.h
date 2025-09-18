// A Mesh is just a list of vertices + indices stored on the GPU.
// Vertex has a position and a color (no normals/UVs for this project).
#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void Draw(); // draw with glDrawElements

    // Accessors (handy for composing meshes)
    std::vector<Vertex> getVertices() const { return vertices; }
    std::vector<unsigned int> getIndices() const { return indices; }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO; // OpenGL buffer handles
};
