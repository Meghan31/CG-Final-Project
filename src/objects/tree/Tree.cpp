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

    // CHANGED: Adjust trunk proportions - reduce width by 25%, increase height by 25%
    float overallScale = 1.5f;  
    float trunkHeight = 1.5f * heightScale * overallScale;  // Increased from 1.2f to 1.5f (25% height increase)
    float foliageHeight = 3.0f * heightScale * foliageScale * overallScale;
    
    // TRUNK - Create realistic irregular trunk (12-sided with varying radius)
    int trunkSides = 12;  // More sides for smoother appearance
    float baseRadius = 0.6f * overallScale;  // Reduced from 0.8f to 0.6f (25% width reduction)
    float topRadius = 0.375f * overallScale; // Reduced from 0.5f to 0.375f (25% width reduction)
    glm::vec3 trunkColor(0.4f, 0.25f, 0.1f);
    
    // Bottom circle of trunk with irregular shape
    for (int i = 0; i < trunkSides; ++i) {
        float angle = 2.0f * M_PI * i / trunkSides;
        // Add irregularity to make it look like a real trunk - adjusted for medium radius
        float radiusVariation = baseRadius + 0.15f * sin(angle * 3.0f) + 0.075f * cos(angle * 7.0f);  // Reduced variation for smaller trunk
        float x = radiusVariation * cos(angle);
        float z = radiusVariation * sin(angle);
        vertices.push_back({{x, 0.0f, z}, trunkColor});
    }
    
    // Top circle of trunk with different irregular shape (tapered)
    for (int i = 0; i < trunkSides; ++i) {
        float angle = 2.0f * M_PI * i / trunkSides;
        // Different irregularity pattern for top + tapering - adjusted for medium radius
        float radiusVariation = topRadius + 0.075f * sin(angle * 4.0f) + 0.045f * cos(angle * 6.0f);  // Reduced variation for smaller trunk
        float x = radiusVariation * cos(angle);
        float z = radiusVariation * sin(angle);
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
        float layerRadius = (2.4f - 0.6f * layer) * foliageScale * overallScale; // Larger foliage, tapers from 2.4 to 0.6
        
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