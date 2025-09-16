#include "Target.h"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
using namespace std;

Mesh createTarget() {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    // Stand (black pole)
    float sw = 0.08f, sh = 1.2f, sd = 0.08f;
    glm::vec3 standColor(0.1f, 0.1f, 0.1f);
    glm::vec3 s[8] = {
        {-sw, 0, -sd}, {sw, 0, -sd}, {sw, 0, sd}, {-sw, 0, sd},
        {-sw, sh, -sd}, {sw, sh, -sd}, {sw, sh, sd}, {-sw, sh, sd}
    };
    
    unsigned int standIndices[] = {
        0,1,2, 2,3,0,       // bottom
        4,5,6, 6,7,4,       // top
        0,1,5, 5,4,0,       // front
        2,3,7, 7,6,2,       // back
        0,3,7, 7,4,0,       // left
        1,2,6, 6,5,1        // right
    };
    
    for (int i = 0; i < 8; i++) vertices.push_back({s[i], standColor});
    indices.insert(indices.end(), begin(standIndices), end(standIndices));

    // Target Board with Concentric Circles
    float boardRadius = 0.6f;
    float boardThickness = 0.05f;
    float yPos = sh + 0.1f; // Slightly above the stand
    int circleSegments = 16;
    int rings = 5; // 5 concentric rings
    
    // Colors for alternating rings (traditional archery target)
    vector<glm::vec3> ringColors = {
        {1.0f, 1.0f, 1.0f},  // White (outermost)
        {0.0f, 0.0f, 0.0f},  // Black
        {0.0f, 0.0f, 1.0f},  // Blue
        {1.0f, 0.0f, 0.0f},  // Red
        {1.0f, 1.0f, 0.0f}   // Gold (center)
    };
    
    unsigned int boardBaseIndex = vertices.size();
    
    // Center point
    vertices.push_back({{0.0f, yPos, 0.0f}, ringColors[rings-1]});
    
    // Create rings from outside to inside
    for (int ring = 0; ring < rings; ++ring) {
        float outerRadius = boardRadius * (rings - ring) / rings;
        float innerRadius = (ring == rings - 1) ? 0.0f : boardRadius * (rings - ring - 1) / rings;
        glm::vec3 color = ringColors[ring];
        
        unsigned int ringStartIndex = vertices.size();
        
        // Outer ring vertices
        for (int i = 0; i < circleSegments; ++i) {
            float angle = 2.0f * M_PI * i / circleSegments;
            float x = outerRadius * cos(angle);
            float z = outerRadius * sin(angle);
            vertices.push_back({{x, yPos, z}, color});
        }
        
        if (ring < rings - 1) {
            // Inner ring vertices (except for center ring)
            unsigned int innerRingStartIndex = vertices.size();
            for (int i = 0; i < circleSegments; ++i) {
                float angle = 2.0f * M_PI * i / circleSegments;
                float x = innerRadius * cos(angle);
                float z = innerRadius * sin(angle);
                vertices.push_back({{x, yPos, z}, color});
            }
            
            // Create ring triangles
            for (int i = 0; i < circleSegments; ++i) {
                int next = (i + 1) % circleSegments;
                
                // Outer triangle
                indices.push_back(ringStartIndex + i);
                indices.push_back(ringStartIndex + next);
                indices.push_back(innerRingStartIndex + i);
                
                // Inner triangle
                indices.push_back(ringStartIndex + next);
                indices.push_back(innerRingStartIndex + next);
                indices.push_back(innerRingStartIndex + i);
            }
        } else {
            // Center ring - connect to center point
            for (int i = 0; i < circleSegments; ++i) {
                int next = (i + 1) % circleSegments;
                indices.push_back(boardBaseIndex); // center point
                indices.push_back(ringStartIndex + i);
                indices.push_back(ringStartIndex + next);
            }
        }
    }
    
    // Add back face of the board (simple circle)
    float backY = yPos - boardThickness;
    glm::vec3 backColor(0.6f, 0.4f, 0.2f); // Brown back
    
    unsigned int backCenterIndex = vertices.size();
    vertices.push_back({{0.0f, backY, 0.0f}, backColor});
    
    for (int i = 0; i < circleSegments; ++i) {
        float angle = 2.0f * M_PI * i / circleSegments;
        float x = boardRadius * cos(angle);
        float z = boardRadius * sin(angle);
        vertices.push_back({{x, backY, z}, backColor});
    }
    
    // Back face triangles
    for (int i = 0; i < circleSegments; ++i) {
        int next = (i + 1) % circleSegments;
        indices.push_back(backCenterIndex);
        indices.push_back(backCenterIndex + 1 + next);
        indices.push_back(backCenterIndex + 1 + i);
    }

    return Mesh(vertices, indices);
}