#include "Tree.h"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
using namespace std;

Mesh createTree() {
    // Default tree (will be varied in main.cpp)
    return createTreeVariant(1.0f, 1.0f, glm::vec3(0.0f, 0.7f, 0.0f));
}

Mesh createTreeVariant(float heightScale, float foliageScale, const glm::vec3& leafColor) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    float trunkHeight = 1.2f * heightScale;
    float foliageHeight = 1.5f * heightScale * foliageScale;
    
    // TRUNK - Create cylindrical trunk (8-sided)
    int trunkSides = 8;
    float trunkRadius = 0.15f;
    glm::vec3 trunkColor(0.4f, 0.25f, 0.1f);
    
    // Bottom circle of trunk
    for (int i = 0; i < trunkSides; ++i) {
        float angle = 2.0f * M_PI * i / trunkSides;
        float x = trunkRadius * cos(angle);
        float z = trunkRadius * sin(angle);
        vertices.push_back({{x, 0.0f, z}, trunkColor});
    }
    
    // Top circle of trunk
    for (int i = 0; i < trunkSides; ++i) {
        float angle = 2.0f * M_PI * i / trunkSides;
        float x = trunkRadius * cos(angle);
        float z = trunkRadius * sin(angle);
        vertices.push_back({{x, trunkHeight, z}, trunkColor});
    }
    
    // Trunk side faces
    for (int i = 0; i < trunkSides; ++i) {
        int next = (i + 1) % trunkSides;
        
        // Two triangles per side
        indices.push_back(i);
        indices.push_back(i + trunkSides);
        indices.push_back(next);
        
        indices.push_back(i + trunkSides);
        indices.push_back(next + trunkSides);
        indices.push_back(next);
    }
    
    // FOLIAGE - Create organic cone-like foliage with multiple layers
    int foliageSides = 6;
    int foliageLayers = 4;
    unsigned int foliageBaseIndex = vertices.size();
    
    // Create layered foliage (like stacked hexagons getting smaller)
    for (int layer = 0; layer < foliageLayers; ++layer) {
        float layerHeight = trunkHeight + (layer * foliageHeight / foliageLayers);
        float layerRadius = (1.2f - 0.3f * layer) * foliageScale; // Tapers from 1.2 to 0.3
        
        // Vary the green shade slightly per layer for organic look
        glm::vec3 layerColor = leafColor;
        layerColor.g += (layer % 2) * 0.1f - 0.05f; // Slight variation
        
        for (int i = 0; i < foliageSides; ++i) {
            float angle = 2.0f * M_PI * i / foliageSides;
            // Add slight randomness to make it organic
            float randomOffset = 0.1f * sin(layer + i);
            float x = (layerRadius + randomOffset) * cos(angle);
            float z = (layerRadius + randomOffset) * sin(angle);
            vertices.push_back({{x, layerHeight, z}, layerColor});
        }
    }
    
    // Top point of foliage
    vertices.push_back({{0.0f, trunkHeight + foliageHeight, 0.0f}, leafColor});
    unsigned int peakIndex = vertices.size() - 1;
    
    // Connect foliage layers
    for (int layer = 0; layer < foliageLayers - 1; ++layer) {
        unsigned int currentLayerStart = foliageBaseIndex + layer * foliageSides;
        unsigned int nextLayerStart = foliageBaseIndex + (layer + 1) * foliageSides;
        
        for (int i = 0; i < foliageSides; ++i) {
            int next = (i + 1) % foliageSides;
            
            // Connect to next layer
            indices.push_back(currentLayerStart + i);
            indices.push_back(nextLayerStart + i);
            indices.push_back(currentLayerStart + next);
            
            indices.push_back(nextLayerStart + i);
            indices.push_back(nextLayerStart + next);
            indices.push_back(currentLayerStart + next);
        }
    }
    
    // Connect top layer to peak
    unsigned int topLayerStart = foliageBaseIndex + (foliageLayers - 1) * foliageSides;
    for (int i = 0; i < foliageSides; ++i) {
        int next = (i + 1) % foliageSides;
        indices.push_back(topLayerStart + i);
        indices.push_back(topLayerStart + next);
        indices.push_back(peakIndex);
    }
    
    // Connect bottom foliage layer to trunk top
    for (int i = 0; i < min(trunkSides, foliageSides); ++i) {
        int trunkTopIndex = trunkSides + i;
        int foliageBottomIndex = foliageBaseIndex + i;
        int nextFoliage = foliageBaseIndex + ((i + 1) % foliageSides);
        
        if (i < foliageSides - 1) {
            indices.push_back(trunkTopIndex);
            indices.push_back(foliageBottomIndex);
            indices.push_back(nextFoliage);
        }
    }

    return Mesh(vertices, indices);
}