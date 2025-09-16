#include "House2.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;

Mesh createHouse2(const glm::vec3& wallColor, const glm::vec3& roofColor) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    // L-shaped house footprint
    float height = 3.0f;
    
    // L-shape vertices (clockwise from front-left)
    vector<glm::vec3> footprint = {
        {-2.0f, 0, -1.5f}, // 0: front left
        { 1.0f, 0, -1.5f}, // 1: front right
        { 1.0f, 0,  0.0f}, // 2: inner corner right
        { 2.0f, 0,  0.0f}, // 3: extension right
        { 2.0f, 0,  2.0f}, // 4: back right
        {-2.0f, 0,  2.0f}  // 5: back left
    };
    
    // Create bottom vertices
    for (size_t i = 0; i < footprint.size(); ++i) {
        vertices.push_back({footprint[i], wallColor});
    }
    
    // Create top vertices
    for (size_t i = 0; i < footprint.size(); ++i) {
        vertices.push_back({{footprint[i].x, height, footprint[i].z}, wallColor});
    }
    
    // Create walls (excluding front wall where door will be)
    size_t n = footprint.size();
    for (size_t i = 1; i < n; ++i) { // Skip first wall (front wall)
        size_t next = (i + 1) % n;
        
        // Wall triangles
        indices.insert(indices.end(), {
            (unsigned int)i, (unsigned int)next, (unsigned int)(next + n),
            (unsigned int)(next + n), (unsigned int)(i + n), (unsigned int)i
        });
    }
    
    // Bottom face (triangulated)
    indices.insert(indices.end(), {0, 1, 2, 0, 2, 5, 2, 3, 4, 4, 5, 2});
    
    // Top face (triangulated)  
    indices.insert(indices.end(), {6, 7, 8, 6, 8, 11, 8, 9, 10, 10, 11, 8});
    
    // FRONT WALL with door
    float doorWidth = 1.0f;
    float doorHeight = 2.2f;
    
    // Front wall spans from vertex 0 to vertex 1
    float wallWidth = footprint[1].x - footprint[0].x; // 3.0f
    float doorStart = -doorWidth/2;
    float doorEnd = doorWidth/2;
    
    unsigned int frontBase = vertices.size();
    
    // Left part of front wall
    vertices.push_back({{footprint[0].x, 0, footprint[0].z}, wallColor});         // bottom left
    vertices.push_back({{doorStart, 0, footprint[0].z}, wallColor});              // bottom door left
    vertices.push_back({{doorStart, doorHeight, footprint[0].z}, wallColor});     // top door left
    vertices.push_back({{footprint[0].x, height, footprint[0].z}, wallColor});    // top left
    
    // Right part of front wall
    vertices.push_back({{doorEnd, 0, footprint[0].z}, wallColor});                // bottom door right
    vertices.push_back({{footprint[1].x, 0, footprint[1].z}, wallColor});         // bottom right
    vertices.push_back({{footprint[1].x, height, footprint[1].z}, wallColor});    // top right
    vertices.push_back({{doorEnd, doorHeight, footprint[0].z}, wallColor});       // top door right
    
    // Top part above door
    vertices.push_back({{doorStart, doorHeight, footprint[0].z}, wallColor});     // door top left
    vertices.push_back({{doorEnd, doorHeight, footprint[0].z}, wallColor});       // door top right
    vertices.push_back({{doorEnd, height, footprint[0].z}, wallColor});           // wall top right
    vertices.push_back({{doorStart, height, footprint[0].z}, wallColor});         // wall top left
    
    // Front wall triangles
    // Left section
    indices.insert(indices.end(), {frontBase+0, frontBase+1, frontBase+2, frontBase+2, frontBase+3, frontBase+0});
    // Right section
    indices.insert(indices.end(), {frontBase+4, frontBase+5, frontBase+6, frontBase+6, frontBase+7, frontBase+4});
    // Top section
    indices.insert(indices.end(), {frontBase+8, frontBase+9, frontBase+10, frontBase+10, frontBase+11, frontBase+8});
    
    // DOOR
    unsigned int doorBase = vertices.size();
    glm::vec3 doorColor(0.3f, 0.15f, 0.05f);
    float doorInset = 0.05f;
    
    vertices.push_back({{doorStart, 0, footprint[0].z + doorInset}, doorColor});
    vertices.push_back({{doorEnd, 0, footprint[0].z + doorInset}, doorColor});
    vertices.push_back({{doorEnd, doorHeight, footprint[0].z + doorInset}, doorColor});
    vertices.push_back({{doorStart, doorHeight, footprint[0].z + doorInset}, doorColor});
    
    indices.insert(indices.end(), {doorBase+0, doorBase+1, doorBase+2, doorBase+2, doorBase+3, doorBase+0});
    
    // Door handle
    unsigned int handleBase = vertices.size();
    glm::vec3 handleColor(1.0f, 0.8f, 0.2f);
    float handleSize = 0.03f;
    glm::vec3 handlePos(doorWidth * 0.4f, doorHeight * 0.5f, footprint[0].z + doorInset + 0.01f);
    
    for (int i = 0; i < 8; ++i) {
        float x = handlePos.x + (i & 1 ? handleSize : -handleSize);
        float y = handlePos.y + (i & 2 ? handleSize : -handleSize);
        float z = handlePos.z + (i & 4 ? handleSize : -handleSize);
        vertices.push_back({{x, y, z}, handleColor});
    }
    
    vector<unsigned int> handleIndices = {
        0,1,2, 2,3,0,  4,6,5, 4,7,6,  0,4,7, 7,3,0,  1,2,6, 6,5,1,  0,1,5, 5,4,0,  2,3,7, 7,6,2
    };
    for (unsigned int idx : handleIndices) {
        indices.push_back(handleBase + idx);
    }
    
    // ROOF (multiple peaks for L-shape)
    unsigned int roofBase = vertices.size();
    float roofHeight = 1.2f;
    
    // Add roof base (top of walls)
    for (size_t i = 0; i < footprint.size(); ++i) {
        vertices.push_back({{footprint[i].x, height, footprint[i].z}, roofColor});
    }
    
    // Add roof peaks
    vertices.push_back({{-0.5f, height + roofHeight, 0.25f}, roofColor}); // main peak
    vertices.push_back({{ 1.5f, height + roofHeight, 1.0f}, roofColor});  // extension peak
    
    // Roof triangles
    size_t peakMain = roofBase + n;
    size_t peakExt = roofBase + n + 1;
    
    // Main section roof
    indices.insert(indices.end(), {roofBase+0, roofBase+1, (unsigned int)peakMain});
    indices.insert(indices.end(), {roofBase+1, roofBase+2, (unsigned int)peakMain});
    indices.insert(indices.end(), {roofBase+5, roofBase+0, (unsigned int)peakMain});
    
    // Extension section roof
    indices.insert(indices.end(), {roofBase+2, roofBase+3, (unsigned int)peakExt});
    indices.insert(indices.end(), {roofBase+3, roofBase+4, (unsigned int)peakExt});
    indices.insert(indices.end(), {roofBase+4, roofBase+5, (unsigned int)peakExt});
    indices.insert(indices.end(), {roofBase+5, roofBase+2, (unsigned int)peakExt});
    
    return Mesh(vertices, indices);
}