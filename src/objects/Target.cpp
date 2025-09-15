#include "Target.h"
#include <glm/glm.hpp>
#include <vector>

Mesh createTarget() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Stand (black)
    float sw=0.1f, sh=1.0f, sd=0.1f;
    glm::vec3 standColor(0.0f,0.0f,0.0f);
    glm::vec3 s[8]={
        {-sw,0,-sd},{sw,0,-sd},{sw,0,sd},{-sw,0,sd},
        {-sw,sh,-sd},{sw,sh,-sd},{sw,sh,sd},{-sw,sh,sd}
    };
    unsigned int standIndices[]={
        0,1,2,2,3,0,
        4,5,6,6,7,4,
        0,1,5,5,4,0,
        2,3,7,7,6,2,
        0,3,7,7,4,0,
        1,2,6,6,5,1
    };
    for(int i=0;i<8;i++) vertices.push_back({s[i],standColor});
    indices.insert(indices.end(), std::begin(standIndices), std::end(standIndices));

    // Board (white)
    float bw=0.8f, bh=0.8f, bd=0.05f;
    float yBase = sh; 
    glm::vec3 boardColor(1.0f,1.0f,1.0f);
    glm::vec3 b[8]={
        {-bw,yBase,-bd},{bw,yBase,-bd},{bw,yBase,bd},{-bw,yBase,bd},
        {-bw,yBase+bh,-bd},{bw,yBase+bh,-bd},{bw,yBase+bh,bd},{-bw,yBase+bh,bd}
    };
    unsigned int boardIndices[]={
        8,9,10,10,11,8,
        12,13,14,14,15,12,
        8,9,13,13,12,8,
        10,11,15,15,14,10,
        8,11,15,15,12,8,
        9,10,14,14,13,9
    };
    for(int i=0;i<8;i++) vertices.push_back({b[i],boardColor});
    indices.insert(indices.end(), std::begin(boardIndices), std::end(boardIndices));

    return Mesh(vertices, indices);
}
