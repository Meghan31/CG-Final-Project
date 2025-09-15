#include "Tree.h"
#include <glm/glm.hpp>
#include <vector>

Mesh createTree() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Trunk (brown)
    float tw = 0.2f, th = 1.0f, td = 0.2f;
    glm::vec3 trunkColor(0.4f,0.2f,0.0f);
    glm::vec3 t[8] = {
        {-tw,0,-td},{tw,0,-td},{tw,0,td},{-tw,0,td},
        {-tw,th,-td},{tw,th,-td},{tw,th,td},{-tw,th,td}
    };
    unsigned int trunkIndices[]={
        0,1,2,2,3,0,
        4,5,6,6,7,4,
        0,1,5,5,4,0,
        2,3,7,7,6,2,
        0,3,7,7,4,0,
        1,2,6,6,5,1
    };
    for(int i=0;i<8;i++) vertices.push_back({t[i], trunkColor});
    indices.insert(indices.end(), std::begin(trunkIndices), std::end(trunkIndices));

    // Leaves (green cube on top)
    float lw=0.8f, lh=0.8f, ld=0.8f;
    glm::vec3 leavesColor(0.0f,0.6f,0.0f);
    glm::vec3 l[8] = {
        {-lw,th,-ld},{lw,th,-ld},{lw,th,ld},{-lw,th,ld},
        {-lw,th+lh,-ld},{lw,th+lh,-ld},{lw,th+lh,ld},{-lw,th+lh,ld}
    };
    unsigned int leavesIndices[]={
        8,9,10,10,11,8,
        12,13,14,14,15,12,
        8,9,13,13,12,8,
        10,11,15,15,14,10,
        8,11,15,15,12,8,
        9,10,14,14,13,9
    };
    for(int i=0;i<8;i++) vertices.push_back({l[i], leavesColor});
    indices.insert(indices.end(), std::begin(leavesIndices), std::end(leavesIndices));

    return Mesh(vertices, indices);
}
