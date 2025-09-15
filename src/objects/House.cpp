// #include "House.h"
// #include <glm/glm.hpp>
// #include <vector>

// Mesh createHouse() {
//     std::vector<Vertex> vertices;
//     std::vector<unsigned int> indices;

//     // Walls (cube-like)
//     float w = 1.5f, h = 1.0f, d = 1.5f;
//     glm::vec3 wallColor(0.2f, 0.2f, 0.2f); // whitish-black
//     glm::vec3 v[8] = {
//         {-w,0,-d},{w,0,-d},{w,0,d},{-w,0,d},
//         {-w,h,-d},{w,h,-d},{w,h,d},{-w,h,d}
//     };
//     unsigned int cubeIndices[] = {
//         0,1,2, 2,3,0,
//         4,5,6, 6,7,4,
//         0,1,5, 5,4,0,
//         2,3,7, 7,6,2,
//         0,3,7, 7,4,0,
//         1,2,6, 6,5,1
//     };
//     for (int i=0;i<8;i++) vertices.push_back({v[i], wallColor});
//     indices.insert(indices.end(), std::begin(cubeIndices), std::end(cubeIndices));

//     // Roof (simple pyramid)
//     glm::vec3 roofColor(0.4f, 0.7f, 1.0f); // sky blue
//     glm::vec3 roofPeak(0.0f, h+0.75f, 0.0f);
//     // Add 4 new vertices for roof sides:
//     unsigned int baseStart = vertices.size();
//     vertices.push_back({v[4], roofColor});
//     vertices.push_back({v[5], roofColor});
//     vertices.push_back({v[6], roofColor});
//     vertices.push_back({v[7], roofColor});
//     vertices.push_back({roofPeak, roofColor}); // peak

//     unsigned int peakIndex = baseStart+4;
//     // Triangles
//     indices.insert(indices.end(), {
//         baseStart+0, baseStart+1, peakIndex,
//         baseStart+1, baseStart+2, peakIndex,
//         baseStart+2, baseStart+3, peakIndex,
//         baseStart+3, baseStart+0, peakIndex
//     });

//     return Mesh(vertices, indices);
// }

#include "House.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;
#include "../Mesh.h"

// Use buildExtrudedIndexed helper
static Mesh buildExtrudedIndexed(const std::vector<glm::vec3>& footprint, float height, glm::vec3 color);

Mesh createHouse() {
    std::vector<glm::vec3> footprint = {
        {-1.0f,0, -1.0f}, {1.0f,0, -1.0f}, {1.0f,0, 1.0f}, {-1.0f,0,1.0f}
    };
    Mesh body = buildExtrudedIndexed(footprint, 1.5f, glm::vec3(0.95f,0.95f,0.95f)); // house color

    // Roof
    std::vector<Vertex> roofVerts;
    std::vector<unsigned int> roofIdx;

    roofVerts.push_back({glm::vec3(-1.0f,1.5f,-1.0f), glm::vec3(0.4f,0.7f,1.0f)});
    roofVerts.push_back({glm::vec3(1.0f,1.5f,-1.0f), glm::vec3(0.4f,0.7f,1.0f)});
    roofVerts.push_back({glm::vec3(0.0f,2.0f,0.0f), glm::vec3(0.4f,0.7f,1.0f)});
    roofVerts.push_back({glm::vec3(-1.0f,1.5f,1.0f), glm::vec3(0.4f,0.7f,1.0f)});
    roofVerts.push_back({glm::vec3(1.0f,1.5f,1.0f), glm::vec3(0.4f,0.7f,1.0f)});

    roofIdx = {0,1,2,1,4,2,4,3,2,3,0,2};

    // merge body + roof
    std::vector<Vertex> verts = body.getVertices();
    std::vector<unsigned int> idx = body.getIndices();
    unsigned int base = verts.size();
    verts.insert(verts.end(), roofVerts.begin(), roofVerts.end());
    for(auto i: roofIdx) idx.push_back(base + i);

    return Mesh(verts, idx);
}
