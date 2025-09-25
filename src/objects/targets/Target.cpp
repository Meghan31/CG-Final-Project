// Most of the Board Portion of the code is AI Generated
// Stand (black pole) was hand-coded by me

// Archery-style target: a pole plus a circular board with colored rings.
#include "Target.h"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
using namespace std;

Mesh createTarget() {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    // Written by Megha
    // Stand (black pole) - a simple box so the target has something to sit on
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

    // Circular board with concentric colored rings (built with triangle strips)
    float boardRadius = 0.6f;
    float boardThickness = 0.05f;
    float yCenter = sh + boardRadius; // Center the target vertically above the stand
    float zPos = 0.0f; // Position in front of stand
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
    
    // Create vertical target board (upright on XY plane)
    // Front surface of the target: I go ring by ring from outside to inside
    vertices.push_back({{0.0f, yCenter, zPos}, ringColors[rings-1]}); // Center point


    // AI Generated but refactored it such that it wont go front on eachothers faces

    // Create rings from outside to inside for front surface
    for (int ring = 0; ring < rings; ++ring) {
        float outerRadius = boardRadius * (rings - ring) / rings;
        float innerRadius = (ring == rings - 1) ? 0.0f : boardRadius * (rings - ring - 1) / rings;
        glm::vec3 ringColor = ringColors[ring];
        
        // Create vertices for this ring on front surface (XY plane)
        for (int i = 0; i <= circleSegments; ++i) {
            float angle = 2.0f * M_PI * i / circleSegments;
            float cosAngle = cos(angle);
            float sinAngle = sin(angle);
            
            // Outer edge of ring (on XY plane, Z is constant)
            vertices.push_back({{outerRadius * cosAngle, yCenter + outerRadius * sinAngle, zPos}, ringColor});
            
            // Inner edge of ring (only if not the center ring)
            if (ring < rings - 1) {
                vertices.push_back({{innerRadius * cosAngle, yCenter + innerRadius * sinAngle, zPos}, ringColor});
            }
        }
    }
    
    // Written by Megha
    // refactored the above code to create a back surface with thickness

    // Back surface of the target (same rings but a little behind to give thickness)
    float backZ = zPos - boardThickness;
    unsigned int backBaseIndex = vertices.size();
    
    vertices.push_back({{0.0f, yCenter, backZ}, ringColors[rings-1]}); // Center point
    
    // Create rings for back surface
    for (int ring = 0; ring < rings; ++ring) {
        float outerRadius = boardRadius * (rings - ring) / rings;
        float innerRadius = (ring == rings - 1) ? 0.0f : boardRadius * (rings - ring - 1) / rings;
        glm::vec3 ringColor = ringColors[ring];
        
        for (int i = 0; i <= circleSegments; ++i) {
            float angle = 2.0f * M_PI * i / circleSegments;
            float cosAngle = cos(angle);
            float sinAngle = sin(angle);
            
            vertices.push_back({{outerRadius * cosAngle, yCenter + outerRadius * sinAngle, backZ}, ringColor});
            
            if (ring < rings - 1) {
                vertices.push_back({{innerRadius * cosAngle, yCenter + innerRadius * sinAngle, backZ}, ringColor});
            }
        }
    }
    // AI Generated Code
    // changed little parts of it look like a target not a flat disc
    // Indices for front surface (center fan for the innermost ring, quads for others)
    unsigned int currentIndex = boardBaseIndex + 1; // Start after center point
    
    for (int ring = 0; ring < rings; ++ring) {
        for (int i = 0; i < circleSegments; ++i) {
            if (ring == rings - 1) {
                // Center ring - triangles from center to outer edge
                unsigned int center = boardBaseIndex;
                unsigned int current = currentIndex + i;
                unsigned int next = currentIndex + (i + 1);
                
                indices.insert(indices.end(), {center, current, next});
            } else {
                // Other rings - quads between inner and outer edges
                unsigned int outerCurrent = currentIndex + i * 2;
                unsigned int outerNext = currentIndex + ((i + 1) % circleSegments) * 2;
                unsigned int innerCurrent = currentIndex + i * 2 + 1;
                unsigned int innerNext = currentIndex + ((i + 1) % circleSegments) * 2 + 1;
                
                // Two triangles forming a quad
                indices.insert(indices.end(), {outerCurrent, innerCurrent, outerNext});
                indices.insert(indices.end(), {innerCurrent, innerNext, outerNext});
            }
        }
        
        if (ring == rings - 1) {
            currentIndex += circleSegments + 1;
        } else {
            currentIndex += (circleSegments + 1) * 2;
        }
    }
    
    // Written by Megha
    // refactored the above code to create a back surface with thickness
    // Indices for back surface (reverse winding so the back faces the right way)
    currentIndex = backBaseIndex + 1;
    
    for (int ring = 0; ring < rings; ++ring) {
        for (int i = 0; i < circleSegments; ++i) {
            if (ring == rings - 1) {
                unsigned int center = backBaseIndex;
                unsigned int current = currentIndex + i;
                unsigned int next = currentIndex + (i + 1);
                
                // Reverse winding for back face
                indices.insert(indices.end(), {center, next, current});
            } else {
                unsigned int outerCurrent = currentIndex + i * 2;
                unsigned int outerNext = currentIndex + ((i + 1) % circleSegments) * 2;
                unsigned int innerCurrent = currentIndex + i * 2 + 1;
                unsigned int innerNext = currentIndex + ((i + 1) % circleSegments) * 2 + 1;
                
                // Reverse winding for back face
                indices.insert(indices.end(), {outerCurrent, outerNext, innerCurrent});
                indices.insert(indices.end(), {innerCurrent, outerNext, innerNext});
            }
        }
        
        if (ring == rings - 1) {
            currentIndex += circleSegments + 1;
        } else {
            currentIndex += (circleSegments + 1) * 2;
        }
    }

    //Written by Megha
    // So that the side faces around the outer edge so the board looks like a thin cylinder
    for (int i = 0; i < circleSegments; ++i) {
        // Get the outermost ring vertices
        unsigned int frontOuter1 = boardBaseIndex + 1 + i * 2;
        unsigned int frontOuter2 = boardBaseIndex + 1 + ((i + 1) % circleSegments) * 2;
        unsigned int backOuter1 = backBaseIndex + 1 + i * 2;
        unsigned int backOuter2 = backBaseIndex + 1 + ((i + 1) % circleSegments) * 2;
        
        // Create quad between front and back outer edges
        indices.insert(indices.end(), {frontOuter1, backOuter1, frontOuter2});
        indices.insert(indices.end(), {backOuter1, backOuter2, frontOuter2});
    }

    return Mesh(vertices, indices);
}