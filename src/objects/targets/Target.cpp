// #include "Target.h"
// #include <glm/glm.hpp>
// #include <vector>
// #include <cmath>
// using namespace std;

// Mesh createTarget() {
//     vector<Vertex> vertices;
//     vector<unsigned int> indices;

//     // Stand (black pole)
//     float sw = 0.08f, sh = 1.2f, sd = 0.08f;
//     glm::vec3 standColor(0.1f, 0.1f, 0.1f);
//     glm::vec3 s[8] = {
//         {-sw, 0, -sd}, {sw, 0, -sd}, {sw, 0, sd}, {-sw, 0, sd},
//         {-sw, sh, -sd}, {sw, sh, -sd}, {sw, sh, sd}, {-sw, sh, sd}
//     };
    
//     unsigned int standIndices[] = {
//         0,1,2, 2,3,0,       // bottom
//         4,5,6, 6,7,4,       // top
//         0,1,5, 5,4,0,       // front
//         2,3,7, 7,6,2,       // back
//         0,3,7, 7,4,0,       // left
//         1,2,6, 6,5,1        // right
//     };
    
//     for (int i = 0; i < 8; i++) vertices.push_back({s[i], standColor});
//     indices.insert(indices.end(), begin(standIndices), end(standIndices));

//     // Target Board with Concentric Circles
//     float boardRadius = 0.6f;
//     float boardThickness = 0.05f;
//     float yPos = sh + 0.1f; // Slightly above the stand
//     int circleSegments = 16;
//     int rings = 5; // 5 concentric rings
    
//     // Colors for alternating rings (traditional archery target)
//     vector<glm::vec3> ringColors = {
//         {1.0f, 1.0f, 1.0f},  // White (outermost)
//         {0.0f, 0.0f, 0.0f},  // Black
//         {0.0f, 0.0f, 1.0f},  // Blue
//         {1.0f, 0.0f, 0.0f},  // Red
//         {1.0f, 1.0f, 0.0f}   // Gold (center)
//     };
    
//     unsigned int boardBaseIndex = vertices.size();
    
//     // Center point
//     vertices.push_back({{0.0f, yPos, 0.0f}, ringColors[rings-1]});
    
//     // Create rings from outside to inside
//     for (int ring = 0; ring < rings; ++ring) {
//         float outerRadius = boardRadius * (rings - ring) / rings;
//         float innerRadius = (ring == rings - 1) ? 0.0f : boardRadius * (rings - ring - 1) / rings;
//         glm::vec3 color = ringColors[ring];
        
//         unsigned int ringStartIndex = vertices.size();
        
//         // Outer ring vertices
//         for (int i = 0; i < circleSegments; ++i) {
//             float angle = 2.0f * M_PI * i / circleSegments;
//             float x = outerRadius * cos(angle);
//             float z = outerRadius * sin(angle);
//             vertices.push_back({{x, yPos, z}, color});
//         }
        
//         if (ring < rings - 1) {
//             // Inner ring vertices (except for center ring)
//             unsigned int innerRingStartIndex = vertices.size();
//             for (int i = 0; i < circleSegments; ++i) {
//                 float angle = 2.0f * M_PI * i / circleSegments;
//                 float x = innerRadius * cos(angle);
//                 float z = innerRadius * sin(angle);
//                 vertices.push_back({{x, yPos, z}, color});
//             }
            
//             // Create ring triangles
//             for (int i = 0; i < circleSegments; ++i) {
//                 int next = (i + 1) % circleSegments;
                
//                 // Outer triangle
//                 indices.push_back(ringStartIndex + i);
//                 indices.push_back(ringStartIndex + next);
//                 indices.push_back(innerRingStartIndex + i);
                
//                 // Inner triangle
//                 indices.push_back(ringStartIndex + next);
//                 indices.push_back(innerRingStartIndex + next);
//                 indices.push_back(innerRingStartIndex + i);
//             }
//         } else {
//             // Center ring - connect to center point
//             for (int i = 0; i < circleSegments; ++i) {
//                 int next = (i + 1) % circleSegments;
//                 indices.push_back(boardBaseIndex); // center point
//                 indices.push_back(ringStartIndex + i);
//                 indices.push_back(ringStartIndex + next);
//             }
//         }
//     }
    
//     // Add back face of the board (simple circle)
//     float backY = yPos - boardThickness;
//     glm::vec3 backColor(0.6f, 0.4f, 0.2f); // Brown back
    
//     unsigned int backCenterIndex = vertices.size();
//     vertices.push_back({{0.0f, backY, 0.0f}, backColor});
    
//     for (int i = 0; i < circleSegments; ++i) {
//         float angle = 2.0f * M_PI * i / circleSegments;
//         float x = boardRadius * cos(angle);
//         float z = boardRadius * sin(angle);
//         vertices.push_back({{x, backY, z}, backColor});
//     }
    
//     // Back face triangles
//     for (int i = 0; i < circleSegments; ++i) {
//         int next = (i + 1) % circleSegments;
//         indices.push_back(backCenterIndex);
//         indices.push_back(backCenterIndex + 1 + next);
//         indices.push_back(backCenterIndex + 1 + i);
//     }

//     return Mesh(vertices, indices);
// }



#include "Target.h"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
using namespace std;

Mesh createTarget() {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    // Stand (black pole) - taller to support vertical target
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

    // Vertical Target Board with Concentric Circles
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
    
    // Create vertical target board (standing upright on XY plane)
    // Front surface of the target
    vertices.push_back({{0.0f, yCenter, zPos}, ringColors[rings-1]}); // Center point
    
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
    
    // Back surface of the target (same structure but different Z)
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
    
    // Create indices for front surface
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
    
    // Create indices for back surface (reverse winding for correct normals)
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
    
    // Create side faces to connect front and back
    // This creates the cylindrical edge of the target
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