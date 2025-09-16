#include "Utils.h"
using namespace std;

Mesh buildExtrudedIndexed(const vector<glm::vec3>& footprint, float height, const glm::vec3& color)
{
    vector<Vertex> verts;
    vector<unsigned int> idx;

    int n = (int)footprint.size();
    
    // Bottom vertices (at y=0)
    for (int i = 0; i < n; ++i) {
        verts.push_back({ footprint[i], color });
    }

    // Top vertices (at y=height)
    for (int i = 0; i < n; ++i) {
        verts.push_back({ glm::vec3(footprint[i].x, height, footprint[i].z), color });
    }

    // Create side faces (rectangular faces between bottom and top)
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        
        // Two triangles per side face
        // Triangle 1: bottom[i], top[i], bottom[next]
        idx.push_back(i); 
        idx.push_back(i + n); 
        idx.push_back(next);
        
        // Triangle 2: top[i], top[next], bottom[next]
        idx.push_back(i + n); 
        idx.push_back(next + n); 
        idx.push_back(next);
    }

    // Bottom face (triangulated as fan from vertex 0)
    for (int i = 1; i < n - 1; ++i) {
        idx.push_back(0);        // center vertex
        idx.push_back(i + 1);    // next vertex
        idx.push_back(i);        // current vertex
    }

    // Top face (triangulated as fan from vertex n)
    for (int i = 1; i < n - 1; ++i) {
        idx.push_back(n);        // center vertex (top)
        idx.push_back(n + i);    // current vertex (top)
        idx.push_back(n + i + 1); // next vertex (top)
    }

    return Mesh(verts, idx);
}