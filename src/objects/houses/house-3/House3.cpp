#include "House3.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;

Mesh createHouse3(const glm::vec3& wallColor, const glm::vec3& roofColor) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    // Square house with front porch
    float houseSize = 3.0f;
    float porchDepth = 1.0f;
    float height = 3.0f;
    float porchHeight = 2.5f;
    
    // MAIN HOUSE (square)
    unsigned int houseBase = vertices.size();
    
    // House base vertices
    vertices.push_back({{-houseSize/2, 0, 0}, wallColor});              // 0: front left
    vertices.push_back({{ houseSize/2, 0, 0}, wallColor});              // 1: front right
    vertices.push_back({{ houseSize/2, 0, houseSize}, wallColor});      // 2: back right
    vertices.push_back({{-houseSize/2, 0, houseSize}, wallColor});      // 3: back left
    
    // House top vertices
    vertices.push_back({{-houseSize/2, height, 0}, wallColor});         // 4: front left top
    vertices.push_back({{ houseSize/2, height, 0}, wallColor});         // 5: front right top
    vertices.push_back({{ houseSize/2, height, houseSize}, wallColor}); // 6: back right top
    vertices.push_back({{-houseSize/2, height, houseSize}, wallColor}); // 7: back left top
    
    // House walls (except front wall)
    // Back wall
    indices.insert(indices.end(), {houseBase+2, houseBase+3, houseBase+7, houseBase+7, houseBase+6, houseBase+2});
    // Left wall
    indices.insert(indices.end(), {houseBase+3, houseBase+0, houseBase+4, houseBase+4, houseBase+7, houseBase+3});
    // Right wall
    indices.insert(indices.end(), {houseBase+1, houseBase+2, houseBase+6, houseBase+6, houseBase+5, houseBase+1});
    // Top
    indices.insert(indices.end(), {houseBase+4, houseBase+5, houseBase+6, houseBase+6, houseBase+7, houseBase+4});
    // Bottom
    indices.insert(indices.end(), {houseBase+0, houseBase+1, houseBase+2, houseBase+2, houseBase+3, houseBase+0});
    
    // FRONT WALL with door opening
    float doorWidth = 1.0f;
    float doorHeight = 2.2f;
    
    unsigned int frontBase = vertices.size();
    
    // Front wall sections around door
    vertices.push_back({{-houseSize/2, 0, 0}, wallColor});              // left bottom
    vertices.push_back({{-doorWidth/2, 0, 0}, wallColor});              // door left bottom
    vertices.push_back({{-doorWidth/2, doorHeight, 0}, wallColor});     // door left top
    vertices.push_back({{-houseSize/2, height, 0}, wallColor});         // left top
    
    vertices.push_back({{ doorWidth/2, 0, 0}, wallColor});              // door right bottom
    vertices.push_back({{ houseSize/2, 0, 0}, wallColor});              // right bottom
    vertices.push_back({{ houseSize/2, height, 0}, wallColor});         // right top
    vertices.push_back({{ doorWidth/2, doorHeight, 0}, wallColor});     // door right top
    
    vertices.push_back({{-doorWidth/2, doorHeight, 0}, wallColor});     // above door left
    vertices.push_back({{ doorWidth/2, doorHeight, 0}, wallColor});     // above door right
    vertices.push_back({{ doorWidth/2, height, 0}, wallColor});         // above door right top
    vertices.push_back({{-doorWidth/2, height, 0}, wallColor});         // above door left top
    
    // Front wall triangles
    indices.insert(indices.end(), {frontBase+0, frontBase+1, frontBase+2, frontBase+2, frontBase+3, frontBase+0});
    indices.insert(indices.end(), {frontBase+4, frontBase+5, frontBase+6, frontBase+6, frontBase+7, frontBase+4});
    indices.insert(indices.end(), {frontBase+8, frontBase+9, frontBase+10, frontBase+10, frontBase+11, frontBase+8});
    
    // PORCH
    unsigned int porchBase = vertices.size();
    glm::vec3 porchColor = wallColor * 0.9f; // Slightly darker
    
    // Porch floor
    vertices.push_back({{-houseSize/2, 0.1f, 0}, porchColor});               // floor back left
    vertices.push_back({{ houseSize/2, 0.1f, 0}, porchColor});               // floor back right
    vertices.push_back({{ houseSize/2, 0.1f, -porchDepth}, porchColor});     // floor front right
    vertices.push_back({{-houseSize/2, 0.1f, -porchDepth}, porchColor});     // floor front left
    
    // Porch floor triangles
    indices.insert(indices.end(), {porchBase+0, porchBase+1, porchBase+2, porchBase+2, porchBase+3, porchBase+0});
    
    // Porch columns (simple)
    for (int i = 0; i < 2; ++i) {
        float x = (i == 0) ? -houseSize/2 + 0.2f : houseSize/2 - 0.2f;
        unsigned int colBase = vertices.size();
        
        float colSize = 0.1f;
        // Column base
        vertices.push_back({{x - colSize, 0.1f, -porchDepth + 0.2f}, porchColor});
        vertices.push_back({{x + colSize, 0.1f, -porchDepth + 0.2f}, porchColor});
        vertices.push_back({{x + colSize, porchHeight, -porchDepth + 0.2f}, porchColor});
        vertices.push_back({{x - colSize, porchHeight, -porchDepth + 0.2f}, porchColor});
        
        // Simple column face
        indices.insert(indices.end(), {colBase+0, colBase+1, colBase+2, colBase+2, colBase+3, colBase+0});
    }
    
    // DOOR
    unsigned int doorBase = vertices.size();
    glm::vec3 doorColor(0.5f, 0.25f, 0.1f);
    float doorInset = 0.05f;
    
    vertices.push_back({{-doorWidth/2, 0, doorInset}, doorColor});
    vertices.push_back({{ doorWidth/2, 0, doorInset}, doorColor});
    vertices.push_back({{ doorWidth/2, doorHeight, doorInset}, doorColor});
    vertices.push_back({{-doorWidth/2, doorHeight, doorInset}, doorColor});
    
    indices.insert(indices.end(), {doorBase+0, doorBase+1, doorBase+2, doorBase+2, doorBase+3, doorBase+0});
    
    // Door handle
    unsigned int handleBase = vertices.size();
    glm::vec3 handleColor(1.0f, 0.8f, 0.2f);
    float handleSize = 0.03f;
    glm::vec3 handlePos(doorWidth * 0.4f, doorHeight * 0.5f, doorInset + 0.01f);
    
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
    
    // ROOF (hip roof style)
    unsigned int roofBase = vertices.size();
    float roofHeight = 1.5f;
    
    // Roof base (top of house)
    vertices.push_back({{-houseSize/2, height, 0}, roofColor});         // front left
    vertices.push_back({{ houseSize/2, height, 0}, roofColor});         // front right
    vertices.push_back({{ houseSize/2, height, houseSize}, roofColor}); // back right
    vertices.push_back({{-houseSize/2, height, houseSize}, roofColor}); // back left
    
    // Roof peak
    vertices.push_back({{0, height + roofHeight, houseSize/2}, roofColor}); // center peak
    
    // Roof triangles
    indices.insert(indices.end(), {roofBase+0, roofBase+1, roofBase+4}); // front
    indices.insert(indices.end(), {roofBase+1, roofBase+2, roofBase+4}); // right
    indices.insert(indices.end(), {roofBase+2, roofBase+3, roofBase+4}); // back
    indices.insert(indices.end(), {roofBase+3, roofBase+0, roofBase+4}); // left
    
    return Mesh(vertices, indices);
}