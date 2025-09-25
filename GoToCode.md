# GoToCode - Code Authorship Documentation

This document provides a detailed breakdown of code authorship across all C++ source files in the MyTownProject, categorizing code blocks as written by Me(Megha), AI-generated, or mixed collaboration.

---

## 📁 **src/main.cpp**

### **Mixed Code (Written by Me + AI)**

- **Lines 1-10**: Header comments and project setup information
- **Lines 11-100**: GLFW/GLAD/GLM includes and boilerplate setup (based on learnopengl.com with AI assistance)
- **Lines 101-250**: Main function initialization and object generation setup (AI-generated with my modifications for collision checks)

### **Written by Me**

- **Lines 351-382**: `key_callback()` function - Mode switching functionality
- **Lines 384-408**: `getProjectionMatrix()` function - View mode projection matrices
- **Lines 410-425**: `getViewMatrix()` function - View mode view matrices
- **Lines 427-432**: `updateOverheadCamera()` function - Overhead camera position updates
- **Lines 548-552**: `checkCollision()` function - Object collision detection
- **Lines 554-580**: `checkAllCollisions()` function - Scene-wide collision checking

### **AI Generated**

- **Lines 499-530**: `mouse_callback()` function - Standard boilerplate mouse handling
- **Lines 532-546**: `getRandomPosition()` function - AI generated with slight modifications
- **Lines 581-601**: `findSafeSpawnPosition()` function - AI generated with edge position modifications by me

---

## 📁 **src/rendering/camera/Camera.cpp**

### **Mixed Code (Written by Me + AI)**

- **Entire file**: Standard boilerplate camera class based on learnopengl.com
- **Modified by Me**: First-person controller adaptations, Y-axis height locking, XZ-plane movement

### **Written by Me**

- Camera movement restrictions to maintain eye-level height
- First-person walking mechanics on XZ plane

---

## 📁 **src/Shader.cpp**

### **AI Generated**

- **Entire file**: Standard shader class for GLSL file loading and compilation
- **Reference**: Based on learnopengl.com tutorials
- **Purpose**: Loads vertex/fragment shaders, compiles and links shader programs

---

## 📁 **src/rendering/mesh/Mesh.cpp**

### **AI Generated**

- **Entire file**: Mesh class for GPU buffer management (VAO/VBO/EBO)
- **Reference**: Based on learnopengl.com with modifications for project needs
- **Purpose**: Handles vertex data upload and rendering

---

## 📁 **src/objects/land/Land.cpp**

### **Written by Me**

- **Entire file**: Ground plane generation
- **Lines 1-27**: Creates a large green quad at y=0 for the scene ground
- **Future plans**: Will integrate with Utils.cpp for closed terrain generation

---

## 📁 **src/objects/houses/house-1/House1.cpp**

### **Mixed Code (Written by Me + AI)**

- **Lines 1-50**: House structure and wall generation (Written by Me)
- **Lines 51-100**: Roof triangulation (Written by Me)
- **Lines 101-144**: Door generation (AI assisted with my modifications)

### **Written by Me**

- Basic house box structure
- Triangular roof geometry
- Manual vertex and index construction

### **AI Generated**

- Door geometry and positioning
- Some texture coordinate calculations

---

## 📁 **src/objects/houses/house-2/House2.cpp**

### **Written by Me**

- **Entire file**: L-shaped house using utility functions
- **Integration**: Uses `buildExtrudedIndexed()` from Utils.cpp
- **Geometry**: More complex footprint than House1

---

## 📁 **src/objects/houses/house-3/House3.cpp**

### **Written by Me**

- **Entire file**: Multi-story house variant
- **Features**: Different proportions and scaling from other house types

---

## 📁 **src/objects/tree/Tree.cpp**

### **Mixed Code (Written by Me + AI)**

- **Lines 1-50**: Started with cone-on-cylinder approach
- **Lines 51-100**: Irregular foliage generation (AI assisted)
- **Lines 101-136**: Trunk geometry (Hand-coded using Target.cpp as reference)

### **Written by Me**

- Trunk cylinder geometry
- Tree scaling and variant system

### **AI Generated**

- Irregular leaf/foliage patterns
- Advanced foliage layering

---

## 📁 **src/objects/targets/Target.cpp**

### **Mixed Code (Written by Me + AI)**

- **Lines 1-50**: Target stand/pole geometry (Written by Me)
- **Lines 51-150**: Circular board with colored rings (AI Generated)
- **Lines 151-193**: Assembly and positioning (Written by Me)

### **Written by Me**

- Black pole/stand structure
- Target positioning and assembly

### **AI Generated**

- Circular target board geometry
- Ring pattern and color calculations

---

## 📁 **src/utils/Utils.cpp**

### **Written by Me**

- **Entire file**: Utility functions for 3D geometry extrusion
- **Lines 1-57**: `buildExtrudedIndexed()` function for creating 3D prisms from 2D footprints
- **Reference**: Built using House1.cpp as reference
- **Future use**: Designed for cars, enemy hitboxes, and other box-shaped objects

---

## 📊 **Code Authorship Summary**

### **Files Primarily Written by Me:**

- `src/objects/land/Land.cpp`
- `src/objects/houses/house-2/House2.cpp`
- `src/objects/houses/house-3/House3.cpp`
- `src/utils/Utils.cpp`

### **Files with Mixed Authorship:**

- `src/main.cpp`
- `src/rendering/camera/Camera.cpp`
- `src/objects/houses/house-1/House1.cpp`
- `src/objects/tree/Tree.cpp`
- `src/objects/targets/Target.cpp`

### **Files Primarily AI Generated:**

- `src/Shader.cpp` (Standard template with AI assistance)
- `src/rendering/mesh/Mesh.cpp` (Standard template with AI assistance)

---

## 📝 **Notes**

1. **Excluded Files**: `glad.c`, files in `glad/` and `KHR/` folders are third-party libraries
2. **Reference Materials**: learnopengl.com used as primary educational resource and Github Projects
3. **Development Style**: Hand-coded geometry construction with selective AI assistance for complex mathematical operations
4. **Future Plans**: Utils.cpp designed for extensibility to support additional object types

---
