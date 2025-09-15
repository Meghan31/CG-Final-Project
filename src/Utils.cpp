#include "Utils.h"

Mesh buildExtrudedIndexed(const std::vector<glm::vec3>& footprint, float height, const glm::vec3& color)
{
    std::vector<Vertex> verts;
    std::vector<unsigned int> idx;

    int n = (int)footprint.size();
    // bottom vertices
    for (int i = 0; i < n; ++i)
        verts.push_back({ footprint[i], color });

    // top vertices
    for (int i = 0; i < n; ++i)
        verts.push_back({ glm::vec3(footprint[i].x, height, footprint[i].z), color });

    // sides
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        idx.push_back(i); idx.push_back(i + n); idx.push_back(next);
        idx.push_back(i + n); idx.push_back(next + n); idx.push_back(next);
    }

    // bottom face (fan)
    for (int i = 1; i < n - 1; ++i) {
        idx.push_back(0);
        idx.push_back(i + 1);
        idx.push_back(i);
    }

    // top face (fan)
    for (int i = 1; i < n - 1; ++i) {
        idx.push_back(n);
        idx.push_back(n + i);
        idx.push_back(n + i + 1);
    }

    return Mesh(verts, idx);
}
