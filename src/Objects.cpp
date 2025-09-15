#include "Objects.h"

// Very simple placeholder geometry (triangles making star footprint etc.)
Mesh createHouse() {
    std::vector<Vertex> v = {
        {{-1,0,-1},{1,0,0}}, {{1,0,-1},{1,0,0}}, {{0,1,-1},{1,0,0}}, // front wall
        {{-1,0,1},{1,0,0}}, {{1,0,1},{1,0,0}}, {{0,1,1},{1,0,0}},   // back wall
    };
    return Mesh(v);
}

Mesh createTree() {
    std::vector<Vertex> v = {
        {{0,0,0},{0,1,0}}, {{0.2f,0,0},{0,1,0}}, {{0.1f,1,0},{0,1,0}},
    };
    return Mesh(v);
}

Mesh createTarget() {
    std::vector<Vertex> v = {
        {{-0.5f,0,-0.5f},{0,0,1}}, {{0.5f,0,-0.5f},{0,0,1}}, {{0.0f,1,-0.5f},{0,0,1}},
    };
    return Mesh(v);
}
