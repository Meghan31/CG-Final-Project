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
    vector<glm::vec3> footprint;
    
    // Create different house shapes
    if (type == 0) {
        // L-shaped house
        footprint = {
            {-1.5f, 0, -1.0f}, {0.0f, 0, -1.0f}, {0.0f, 0, 0.0f},
            {1.0f, 0, 0.0f}, {1.0f, 0, 1.5f}, {-1.5f, 0, 1.5f}
        };
    } else if (type == 1) {
        // Rectangular house
        footprint = {
            {-1.2f, 0, -0.8f}, {1.2f, 0, -0.8f}, 
            {1.2f, 0, 1.2f}, {-1.2f, 0, 1.2f}
        };
    } else {
        // Square house
        footprint = {
            {-1.0f, 0, -1.0f}, {1.0f, 0, -1.0f}, 
            {1.0f, 0, 1.0f}, {-1.0f, 0, 1.0f}
        };
    }
    
    float houseHeight = 1.5f;
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
    
    // Add roof peak
    roofVerts.push_back({
        glm::vec3(center.x, houseHeight + 0.8f, center.z), 
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

    return Mesh(allVerts, allIdx);
}