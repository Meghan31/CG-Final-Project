// All of this code was written by Megha and used House1.cpp as a reference for style and structure.

// House type 2: a simple cabin made by extruding a rectangle and adding a flat roof.
// I used a helper to extrude the footprint to keep this file short.
#include "House2.h"
#include "../../../utils/Utils.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;

Mesh createHouse2(const glm::vec3& wallColor, const glm::vec3& roofColor) {
    (void)roofColor; // I keep the parameter for API consistency, but don't use it here
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    // Simple rectangular cabin footprint - smaller than other houses
    float width = 4.0f;   // Cabin width
    float depth = 3.0f;   // Cabin depth  
    float height = 5.0f;  // Cabin height
    
    vector<glm::vec3> footprint = {
        {-width/2, 0, -depth/2},  // Front left
        { width/2, 0, -depth/2},  // Front right
        { width/2, 0,  depth/2},  // Back right
        {-width/2, 0,  depth/2}   // Back left
    };
    
    // Create cabin body by extruding the 2D footprint to a 3D shape using our utility function
    Mesh bodyMesh = buildExtrudedIndexed(footprint, height, wallColor);
    vector<Vertex> bodyVertices = bodyMesh.getVertices();
    vector<unsigned int> bodyIndices = bodyMesh.getIndices();
    
    // Add body to main mesh (merge the generated vertices/indices)
    vertices.insert(vertices.end(), bodyVertices.begin(), bodyVertices.end());
    indices.insert(indices.end(), bodyIndices.begin(), bodyIndices.end());
    
    // Add door to front wall (push it a tiny bit forward to avoid z-fighting with the wall)
    unsigned int doorBase = vertices.size();
    float doorWidth = 1.5f;
    float doorHeight = 3.5f;
    glm::vec3 doorColor(0.4f, 0.2f, 0.1f); // Dark brown
    
    // Place door slightly in front of wall plane (negative Z) to avoid z-fighting
    float doorInset = -0.02f;
    vertices.push_back({{-doorWidth/2, 0, -depth/2 + doorInset}, doorColor});
    vertices.push_back({{ doorWidth/2, 0, -depth/2 + doorInset}, doorColor});
    vertices.push_back({{ doorWidth/2, doorHeight, -depth/2 + doorInset}, doorColor});
    vertices.push_back({{-doorWidth/2, doorHeight, -depth/2 + doorInset}, doorColor});
    
    // Door face
    indices.insert(indices.end(), {doorBase+0, doorBase+1, doorBase+2});
    indices.insert(indices.end(), {doorBase+2, doorBase+3, doorBase+0});
    
    // Simple flat roof - I picked a neutral grey color
    glm::vec3 greyRoofColor(0.5f, 0.5f, 0.5f); // Plain grey
    unsigned int roofBase = vertices.size();
    
    // Roof extends slightly beyond walls (tiny overhang looks nicer)
    float roofOverhang = 0.3f;
    float roofThickness = 0.2f;
    
    // Bottom face of roof (ceiling)
    vertices.push_back({{-width/2 - roofOverhang, height, -depth/2 - roofOverhang}, greyRoofColor});
    vertices.push_back({{ width/2 + roofOverhang, height, -depth/2 - roofOverhang}, greyRoofColor});
    vertices.push_back({{ width/2 + roofOverhang, height,  depth/2 + roofOverhang}, greyRoofColor});
    vertices.push_back({{-width/2 - roofOverhang, height,  depth/2 + roofOverhang}, greyRoofColor});
    
    // Top face of roof
    vertices.push_back({{-width/2 - roofOverhang, height + roofThickness, -depth/2 - roofOverhang}, greyRoofColor});
    vertices.push_back({{ width/2 + roofOverhang, height + roofThickness, -depth/2 - roofOverhang}, greyRoofColor});
    vertices.push_back({{ width/2 + roofOverhang, height + roofThickness,  depth/2 + roofOverhang}, greyRoofColor});
    vertices.push_back({{-width/2 - roofOverhang, height + roofThickness,  depth/2 + roofOverhang}, greyRoofColor});
    
    // Bottom face triangles
    indices.insert(indices.end(), {roofBase+0, roofBase+1, roofBase+2});
    indices.insert(indices.end(), {roofBase+2, roofBase+3, roofBase+0});
    
    // Top face triangles
    indices.insert(indices.end(), {roofBase+4, roofBase+6, roofBase+5});
    indices.insert(indices.end(), {roofBase+6, roofBase+4, roofBase+7});
    
    // Roof edge faces (connect top and bottom with quads)
    // Front edge
    indices.insert(indices.end(), {roofBase+0, roofBase+1, roofBase+5});
    indices.insert(indices.end(), {roofBase+5, roofBase+4, roofBase+0});
    
    // Right edge  
    indices.insert(indices.end(), {roofBase+1, roofBase+2, roofBase+6});
    indices.insert(indices.end(), {roofBase+6, roofBase+5, roofBase+1});
    
    // Back edge
    indices.insert(indices.end(), {roofBase+2, roofBase+3, roofBase+7});
    indices.insert(indices.end(), {roofBase+7, roofBase+6, roofBase+2});
    
    // Left edge
    indices.insert(indices.end(), {roofBase+3, roofBase+0, roofBase+4});
    indices.insert(indices.end(), {roofBase+4, roofBase+7, roofBase+3});
    
    // Add simple door handle (a small cube near the right side of the door)
    unsigned int handleBase = vertices.size();
    glm::vec3 handleColor(0.8f, 0.6f, 0.2f); // Bronze color
    float handleSize = 0.08f;
    // Handle protrudes outward from the door (further toward negative Z)
    glm::vec3 handlePos(doorWidth * 0.35f, doorHeight * 0.5f, -depth/2 + doorInset - 0.02f);
    
    // Simple cube handle
    vertices.push_back({{handlePos.x - handleSize, handlePos.y - handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y - handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y + handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x - handleSize, handlePos.y + handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x - handleSize, handlePos.y - handleSize, handlePos.z + handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y - handleSize, handlePos.z + handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y + handleSize, handlePos.z + handleSize}, handleColor});
    vertices.push_back({{handlePos.x - handleSize, handlePos.y + handleSize, handlePos.z + handleSize}, handleColor});
    
    // Handle cube faces
    vector<unsigned int> handleIndices = {
        0,1,2, 2,3,0,  // front
        4,6,5, 4,7,6,  // back  
        0,4,7, 7,3,0,  // left
        1,2,6, 6,5,1,  // right
        0,1,5, 5,4,0,  // bottom
        2,3,7, 7,6,2   // top
    };
    
    for (unsigned int idx : handleIndices) {
        indices.push_back(handleBase + idx);
    }
    
    return Mesh(vertices, indices);
}