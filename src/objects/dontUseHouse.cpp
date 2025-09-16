#include "House.h"
#include "../Utils.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;

Mesh createHouse() {
    // Default house (will be varied in main.cpp)
    return createHouseVariant(0, glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.7f, 0.3f, 0.3f));
}

Mesh createHouseVariant(int type, const glm::vec3& wallColor, const glm::vec3& roofColor) {
    // CHANGED: Increased house scale from 1.5x to 2.0x for wider houses
    float houseScale = 2.0f;
    
    vector<glm::vec3> footprint;
    
    // Create different house shapes - scaled up and wider
    if (type == 0) {
        // L-shaped house
        footprint = {
            {-1.5f * houseScale, 0, -1.0f * houseScale}, {0.0f, 0, -1.0f * houseScale}, {0.0f, 0, 0.0f},
            {1.0f * houseScale, 0, 0.0f}, {1.0f * houseScale, 0, 1.5f * houseScale}, {-1.5f * houseScale, 0, 1.5f * houseScale}
        };
    } else if (type == 1) {
        // Rectangular house
        footprint = {
            {-1.2f * houseScale, 0, -0.8f * houseScale}, {1.2f * houseScale, 0, -0.8f * houseScale}, 
            {1.2f * houseScale, 0, 1.2f * houseScale}, {-1.2f * houseScale, 0, 1.2f * houseScale}
        };
    } else {
        // Square house
        footprint = {
            {-1.0f * houseScale, 0, -1.0f * houseScale}, {1.0f * houseScale, 0, -1.0f * houseScale}, 
            {1.0f * houseScale, 0, 1.0f * houseScale}, {-1.0f * houseScale, 0, 1.0f * houseScale}
        };
    }
    
    // House height remains 3x increase
    float houseHeight = 4.5f;
    Mesh body = buildExtrudedIndexed(footprint, houseHeight, wallColor);

    // Create roof
    vector<Vertex> roofVerts;
    vector<unsigned int> roofIdx;

    // Calculate roof peak position (center of footprint)
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    for (const auto& point : footprint) {
        center.x += point.x;
        center.z += point.z;
    }
    center.x /= footprint.size();
    center.z /= footprint.size();
    
    // Add roof base vertices (top of walls)
    for (size_t i = 0; i < footprint.size(); ++i) {
        roofVerts.push_back({
            glm::vec3(footprint[i].x, houseHeight, footprint[i].z), 
            roofColor
        });
    }
    
    // Add roof peak - also increased roof height proportionally
    roofVerts.push_back({
        glm::vec3(center.x, houseHeight + 2.4f, center.z), // Increased from 0.8f to 2.4f (3x)
        roofColor
    });
    
    // Create roof triangles (from each edge to peak)
    unsigned int peakIndex = footprint.size();
    for (size_t i = 0; i < footprint.size(); ++i) {
        unsigned int next = (i + 1) % footprint.size();
        roofIdx.push_back(i);
        roofIdx.push_back(next);
        roofIdx.push_back(peakIndex);
    }

    // Merge body and roof
    vector<Vertex> allVerts = body.getVertices();
    vector<unsigned int> allIdx = body.getIndices();
    unsigned int baseIndex = allVerts.size();
    
    allVerts.insert(allVerts.end(), roofVerts.begin(), roofVerts.end());
    for (auto i : roofIdx) {
        allIdx.push_back(baseIndex + i);
    }

    // ADD DOOR - FIXED AND SIMPLIFIED
    // Door dimensions (slightly taller than human height)
    float doorWidth = 1.0f * houseScale * 0.4f;  // Scale door with house size
    float doorHeight = 2.2f;  // Keep door height reasonable
    float doorDepth = 0.1f;   // More visible depth
    
    // SIMPLIFIED: Always place door on the "front" face (first edge)
    glm::vec3 frontCenter;
    glm::vec3 frontNormal;
    
    if (footprint.size() >= 2) {
        // Get the center of the first edge
        frontCenter = (footprint[0] + footprint[1]) * 0.5f;
        
        // Calculate outward normal for the first edge
        glm::vec3 edge = footprint[1] - footprint[0];
        frontNormal = glm::normalize(glm::vec3(-edge.z, 0, edge.x));
        
        // Move door clearly outside the wall
        frontCenter += frontNormal * doorDepth;
    } else {
        // Fallback for edge case
        frontCenter = glm::vec3(0, 0, houseScale * 1.5f);
        frontNormal = glm::vec3(0, 0, 1);
    }
    
    // Door color (dark brown)
    glm::vec3 doorColor(0.4f, 0.2f, 0.1f);  // More visible brown
    
    unsigned int doorBaseIdx = allVerts.size();
    
    // Create door as a simple rectangular prism
    float hw = doorWidth * 0.5f;  // half width
    float hd = doorDepth * 0.5f;  // half depth
    
    // Door vertices (8 vertices for a rectangular prism)
    // Front face
    allVerts.push_back({{frontCenter.x - hw, 0.0f, frontCenter.z + hd}, doorColor});        // 0: bottom left front
    allVerts.push_back({{frontCenter.x + hw, 0.0f, frontCenter.z + hd}, doorColor});        // 1: bottom right front
    allVerts.push_back({{frontCenter.x + hw, doorHeight, frontCenter.z + hd}, doorColor});  // 2: top right front
    allVerts.push_back({{frontCenter.x - hw, doorHeight, frontCenter.z + hd}, doorColor});  // 3: top left front
    
    // Back face
    allVerts.push_back({{frontCenter.x - hw, 0.0f, frontCenter.z - hd}, doorColor});        // 4: bottom left back
    allVerts.push_back({{frontCenter.x + hw, 0.0f, frontCenter.z - hd}, doorColor});        // 5: bottom right back
    allVerts.push_back({{frontCenter.x + hw, doorHeight, frontCenter.z - hd}, doorColor});  // 6: top right back
    allVerts.push_back({{frontCenter.x - hw, doorHeight, frontCenter.z - hd}, doorColor});  // 7: top left back
    
    // Door faces indices
    vector<unsigned int> doorIndices = {
        // Front face
        0, 1, 2,   2, 3, 0,
        // Back face  
        4, 6, 5,   4, 7, 6,
        // Left face
        4, 0, 3,   3, 7, 4,
        // Right face
        1, 5, 6,   6, 2, 1,
        // Top face
        3, 2, 6,   6, 7, 3,
        // Bottom face
        4, 5, 1,   1, 0, 4
    };
    
    // Add door indices
    for (unsigned int idx : doorIndices) {
        allIdx.push_back(doorBaseIdx + idx);
    }
    
    // Add door handle (more visible)
    glm::vec3 handleColor(0.9f, 0.8f, 0.3f); // Bright brass color
    float handleSize = 0.05f * houseScale;   // Scale handle with house
    glm::vec3 handlePos = frontCenter + glm::vec3(doorWidth * 0.35f, doorHeight * 0.5f, doorDepth * 0.6f);
    
    unsigned int handleBaseIdx = allVerts.size();
    
    // Simple cube for handle (8 vertices)
    allVerts.push_back({{handlePos.x - handleSize, handlePos.y - handleSize, handlePos.z - handleSize}, handleColor});
    allVerts.push_back({{handlePos.x + handleSize, handlePos.y - handleSize, handlePos.z - handleSize}, handleColor});
    allVerts.push_back({{handlePos.x + handleSize, handlePos.y + handleSize, handlePos.z - handleSize}, handleColor});
    allVerts.push_back({{handlePos.x - handleSize, handlePos.y + handleSize, handlePos.z - handleSize}, handleColor});
    allVerts.push_back({{handlePos.x - handleSize, handlePos.y - handleSize, handlePos.z + handleSize}, handleColor});
    allVerts.push_back({{handlePos.x + handleSize, handlePos.y - handleSize, handlePos.z + handleSize}, handleColor});
    allVerts.push_back({{handlePos.x + handleSize, handlePos.y + handleSize, handlePos.z + handleSize}, handleColor});
    allVerts.push_back({{handlePos.x - handleSize, handlePos.y + handleSize, handlePos.z + handleSize}, handleColor});
    
    // Handle cube faces
    vector<unsigned int> handleIndices = {
        0,1,2, 2,3,0,       // front
        4,5,6, 6,7,4,       // back  
        0,1,5, 5,4,0,       // bottom
        2,3,7, 7,6,2,       // top
        0,3,7, 7,4,0,       // left
        1,2,6, 6,5,1        // right
    };
    
    for (unsigned int idx : handleIndices) {
        allIdx.push_back(handleBaseIdx + idx);
    }

    return Mesh(allVerts, allIdx);
}