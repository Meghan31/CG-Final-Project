// Most of this code was written by Megha and used AI to help generate parts of 'DOOR'

// House type 1: a simple box house with a triangular roof and a door.
// I'm building the mesh by pushing vertices and triangle indices by hand.
#include "House1.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;

Mesh createHouse1(const glm::vec3& wallColor, const glm::vec3& roofColor) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    float sizeC= 2.5f; // quick scale so I can make the whole house bigger
    
    // Simple rectangular house - 4m x 3m x 3m
    float width = 4.0f *sizeC;
    float depth = 3.0f *sizeC;
    float height = 3.0f *sizeC;

    // House base vertices (bottom corners of the box)
    vertices.push_back({{-width/2, 0, -depth/2}, wallColor}); // 0: front left
    vertices.push_back({{ width/2, 0, -depth/2}, wallColor}); // 1: front right
    vertices.push_back({{ width/2, 0,  depth/2}, wallColor}); // 2: back right
    vertices.push_back({{-width/2, 0,  depth/2}, wallColor}); // 3: back left
    
    // House top vertices (same XZ but y=height)
    vertices.push_back({{-width/2, height, -depth/2}, wallColor}); // 4: front left top
    vertices.push_back({{ width/2, height, -depth/2}, wallColor}); // 5: front right top
    vertices.push_back({{ width/2, height,  depth/2}, wallColor}); // 6: back right top
    vertices.push_back({{-width/2, height,  depth/2}, wallColor}); // 7: back left top
    
    // House walls (two triangles each) (I skip the front because the door cuts a hole there)
    // Front wall
    // indices.insert(indices.end(), {0, 1, 5, 5, 4, 0});
    // Back wall
    indices.insert(indices.end(), {2, 3, 7, 7, 6, 2});
    // Left wall  
    indices.insert(indices.end(), {3, 0, 4, 4, 7, 3});
    // Right wall
    indices.insert(indices.end(), {1, 2, 6, 6, 5, 1});
    // Top (roof base)
    indices.insert(indices.end(), {4, 5, 6, 6, 7, 4});
    // Bottom
    indices.insert(indices.end(), {0, 1, 2, 2, 3, 0});
    


    // AI GENERATED But changed it most part of it, So It would fit well with the house
    // Front wall with door opening (I split it into left, right, and above-door)
    // float doorWidth = 1.0f * sizeC;
    float doorWidth = 1.2f ;
    // float doorHeight = 2.2f * sizeC;
    float doorHeight = 2.5f ;

    // // Front wall vertices (around door)
    unsigned int frontBase = vertices.size();
    
    // Left side of front wall
    vertices.push_back({{-width/2, 0, -depth/2}, wallColor});          // 8: bottom left
    vertices.push_back({{-doorWidth/2, 0, -depth/2}, wallColor});      // 9: bottom door left
    vertices.push_back({{-doorWidth/2, doorHeight, -depth/2}, wallColor}); // 10: top door left  
    vertices.push_back({{-width/2, height, -depth/2}, wallColor});     // 11: top left
    
    // Right side of front wall
    vertices.push_back({{doorWidth/2, 0, -depth/2}, wallColor});       // 12: bottom door right
    vertices.push_back({{width/2, 0, -depth/2}, wallColor});           // 13: bottom right
    vertices.push_back({{width/2, height, -depth/2}, wallColor});      // 14: top right
    vertices.push_back({{doorWidth/2, doorHeight, -depth/2}, wallColor}); // 15: top door right
    
    // Top part above door
    vertices.push_back({{-doorWidth/2, doorHeight, -depth/2}, wallColor}); // 16: door top left
    vertices.push_back({{doorWidth/2, doorHeight, -depth/2}, wallColor});  // 17: door top right
    vertices.push_back({{doorWidth/2, height, -depth/2}, wallColor});      // 18: wall top right
    vertices.push_back({{-doorWidth/2, height, -depth/2}, wallColor});     // 19: wall top left
    
    // Front wall triangles
    // Left side
    indices.insert(indices.end(), {frontBase+0, frontBase+1, frontBase+2, frontBase+2, frontBase+3, frontBase+0});
    // Right side  
    indices.insert(indices.end(), {frontBase+4, frontBase+5, frontBase+6, frontBase+6, frontBase+7, frontBase+4});
    // Top above door
    indices.insert(indices.end(), {frontBase+8, frontBase+9, frontBase+10, frontBase+10, frontBase+11, frontBase+8});
    
    // DOOR (slightly in front of the wall so it doesn't z-fight)
    unsigned int doorBase = vertices.size();
    glm::vec3 doorColor(0.4f, 0.2f, 0.1f); // Dark brown
    
    // Door vertices: ensure door sits on the exterior of the front wall (slightly outward)
    float doorInset = -0.05f * sizeC;
    vertices.push_back({{-doorWidth/2, 0, -depth/2 + doorInset}, doorColor});     // door bottom left
    vertices.push_back({{ doorWidth/2, 0, -depth/2 + doorInset}, doorColor});     // door bottom right
    vertices.push_back({{ doorWidth/2, doorHeight, -depth/2 + doorInset}, doorColor}); // door top right
    vertices.push_back({{-doorWidth/2, doorHeight, -depth/2 + doorInset}, doorColor}); // door top left
    
    // Door face
    indices.insert(indices.end(), {doorBase+0, doorBase+1, doorBase+2, doorBase+2, doorBase+3, doorBase+0});
    
    // Door handle (a tiny cube so the door looks more real)
    unsigned int handleBase = vertices.size();
    glm::vec3 handleColor(1.0f, 0.8f, 0.2f); // Gold
    // float handleSize = 0.03f * sizeC;
    float handleSize = 0.06f ;
    // Handle should protrude outward from the door (further toward negative Z)
    glm::vec3 handlePos(doorWidth * 0.4f, doorHeight * 0.5f, -depth/2 + doorInset - 0.02f);
    
    // Handle cube
    vertices.push_back({{handlePos.x - handleSize, handlePos.y - handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y - handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y + handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x - handleSize, handlePos.y + handleSize, handlePos.z - handleSize}, handleColor});
    vertices.push_back({{handlePos.x - handleSize, handlePos.y - handleSize, handlePos.z + handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y - handleSize, handlePos.z + handleSize}, handleColor});
    vertices.push_back({{handlePos.x + handleSize, handlePos.y + handleSize, handlePos.z + handleSize}, handleColor});
    vertices.push_back({{handlePos.x - handleSize, handlePos.y + handleSize, handlePos.z + handleSize}, handleColor});
    
    // Handle faces
    vector<unsigned int> handleIndices = {
        0,1,2, 2,3,0,  4,6,5, 4,7,6,  0,4,7, 7,3,0,  1,2,6, 6,5,1,  0,1,5, 5,4,0,  2,3,7, 7,6,2
    };
    for (unsigned int idx : handleIndices) {
        indices.push_back(handleBase + idx);
    }
    

    // Written by Megha
    // ROOF (simple tent/triangular shape that meets at one peak)
    unsigned int roofBase = vertices.size();
    float roofHeight = 1.5f * sizeC;
    
    vertices.push_back({{-width/2, height, -depth/2}, roofColor}); // front left
    vertices.push_back({{ width/2, height, -depth/2}, roofColor}); // front right
    vertices.push_back({{ width/2, height,  depth/2}, roofColor}); // back right
    vertices.push_back({{-width/2, height,  depth/2}, roofColor}); // back left
    vertices.push_back({{0, height + roofHeight, 0}, roofColor});  // roof peak

    // Roof triangles
    indices.insert(indices.end(), {roofBase+0, roofBase+1, roofBase+4}); // front
    indices.insert(indices.end(), {roofBase+1, roofBase+2, roofBase+4}); // right
    indices.insert(indices.end(), {roofBase+2, roofBase+3, roofBase+4}); // back
    indices.insert(indices.end(), {roofBase+3, roofBase+0, roofBase+4}); // left
    
    return Mesh(vertices, indices);
}