# GoToCode - Interactive Code Authorship Documentation

This document provides a detailed breakdown of code authorship across all C++ source files in the MyTownProject, categorizing code blocks as written by Me(Megha), AI-generated, or mixed collaboration.

## 🔗 Quick Navigation

- [Main Application](#main-application)
- [Rendering System](#rendering-system)
- [Objects](#objects)
- [Utilities](#utilities)
- [Third-Party Libraries](#third-party-libraries)

---

## 🏠 Main Application

### 📁 **[src/main.cpp](src/main.cpp)**

**🔗 Quick Links:**

- [Lines 1-10: Header Comments](src/main.cpp#L1-L10)
- [Lines 11-100: Includes & Setup](src/main.cpp#L11-L100)
- [Lines 101-250: Main Initialization](src/main.cpp#L101-L250)
- [Lines 351-382: key_callback()](src/main.cpp#L351-L382)
- [Lines 384-408: getProjectionMatrix()](src/main.cpp#L384-L408)
- [Lines 410-425: getViewMatrix()](src/main.cpp#L410-L425)
- [Lines 427-432: updateOverheadCamera()](src/main.cpp#L427-L432)
- [Lines 548-552: checkCollision()](src/main.cpp#L548-L552)
- [Lines 554-580: checkAllCollisions()](src/main.cpp#L554-L580)
- [Lines 499-530: mouse_callback()](src/main.cpp#L499-L530)
- [Lines 532-546: getRandomPosition()](src/main.cpp#L532-L546)
- [Lines 581-601: findSafeSpawnPosition()](src/main.cpp#L581-L601)

#### **Mixed Code (Written by Me + AI)**

- **[Lines 1-10](src/main.cpp#L1-L10)**: Header comments and project setup information
- **[Lines 11-100](src/main.cpp#L11-L100)**: GLFW/GLAD/GLM includes and boilerplate setup (based on learnopengl.com with AI assistance)
- **[Lines 101-250](src/main.cpp#L101-L250)**: Main function initialization and object generation setup (AI-generated with my modifications for collision checks)

#### **Written by Me**

- **[Lines 351-382](src/main.cpp#L351-L382)**: `key_callback()` function - Mode switching functionality
- **[Lines 384-408](src/main.cpp#L384-L408)**: `getProjectionMatrix()` function - View mode projection matrices
- **[Lines 410-425](src/main.cpp#L410-L425)**: `getViewMatrix()` function - View mode view matrices
- **[Lines 427-432](src/main.cpp#L427-L432)**: `updateOverheadCamera()` function - Overhead camera position updates
- **[Lines 548-552](src/main.cpp#L548-L552)**: `checkCollision()` function - Object collision detection
- **[Lines 554-580](src/main.cpp#L554-L580)**: `checkAllCollisions()` function - Scene-wide collision checking

#### **AI Generated**

- **[Lines 499-530](src/main.cpp#L499-L530)**: `mouse_callback()` function - Standard boilerplate mouse handling
- **[Lines 532-546](src/main.cpp#L532-L546)**: `getRandomPosition()` function - AI generated with slight modifications
- **[Lines 581-601](src/main.cpp#L581-L601)**: `findSafeSpawnPosition()` function - AI generated with edge position modifications by me

---

## 🎨 Rendering System

### 📁 **[src/rendering/camera/Camera.cpp](src/rendering/camera/Camera.cpp)**

**🔗 Quick Links:**

- [Constructor (Lines ~13-25)](src/rendering/camera/Camera.cpp#L13-L25)
- [GetViewMatrix() function](src/rendering/camera/Camera.cpp#L27-L30)
- [ProcessKeyboard() function](src/rendering/camera/Camera.cpp#L32-L60)
- [ProcessMouseMovement() function](src/rendering/camera/Camera.cpp#L62-L75)
- [ProcessMouseScroll() function](src/rendering/camera/Camera.cpp#L77-L81)
- [updateCameraVectors() function](src/rendering/camera/Camera.cpp#L83-L92)

#### **Mixed Code (Written by Me + AI)**

- **[Entire file](src/rendering/camera/Camera.cpp)**: Standard boilerplate camera class based on learnopengl.com
- **Modified by Me**: First-person controller adaptations, Y-axis height locking, XZ-plane movement

#### **Written by Me**

- Camera movement restrictions to maintain eye-level height
- First-person walking mechanics on XZ plane

### 📁 **[src/Shader.cpp](src/Shader.cpp)**

#### **AI Generated**

- **[Entire file](src/Shader.cpp)**: Standard shader class for GLSL file loading and compilation
- **Reference**: Based on learnopengl.com tutorials
- **Purpose**: Loads vertex/fragment shaders, compiles and links shader programs

### 📁 **[src/rendering/mesh/Mesh.cpp](src/rendering/mesh/Mesh.cpp)**

#### **AI Generated**

- **[Entire file](src/rendering/mesh/Mesh.cpp)**: Mesh class for GPU buffer management (VAO/VBO/EBO)
- **Reference**: Based on learnopengl.com with modifications for project needs
- **Purpose**: Handles vertex data upload and rendering

---

## 🏗️ Objects

### 🌍 Land

#### 📁 **[src/objects/land/Land.cpp](src/objects/land/Land.cpp)**

**🔗 Quick Links:**

- [Lines 1-27: Ground Generation](src/objects/land/Land.cpp#L1-L27)

#### **Written by Me**

- **[Entire file](src/objects/land/Land.cpp)**: Ground plane generation
- **[Lines 1-27](src/objects/land/Land.cpp#L1-L27)**: Creates a large green quad at y=0 for the scene ground
- **Future plans**: Will integrate with Utils.cpp for closed terrain generation

### 🏠 Houses

#### 📁 **[src/objects/houses/house-1/House1.cpp](src/objects/houses/house-1/House1.cpp)**

**🔗 Quick Links:**

- [Lines 1-50: House Structure](src/objects/houses/house-1/House1.cpp#L1-L50)
- [Lines 51-100: Roof Triangulation](src/objects/houses/house-1/House1.cpp#L51-L100)
- [Lines 101-144: Door Generation](src/objects/houses/house-1/House1.cpp#L101-L144)

#### **Mixed Code (Written by Me + AI)**

- **[Lines 1-50](src/objects/houses/house-1/House1.cpp#L1-L50)**: House structure and wall generation (Written by Me)
- **[Lines 51-100](src/objects/houses/house-1/House1.cpp#L51-L100)**: Roof triangulation (Written by Me)
- **[Lines 101-144](src/objects/houses/house-1/House1.cpp#L101-L144)**: Door generation (AI assisted with my modifications)

#### **Written by Me**

- Basic house box structure
- Triangular roof geometry
- Manual vertex and index construction

#### **AI Generated**

- Door geometry and positioning
- Some texture coordinate calculations

#### 📁 **[src/objects/houses/house-2/House2.cpp](src/objects/houses/house-2/House2.cpp)**

#### **Written by Me**

- **[Entire file](src/objects/houses/house-2/House2.cpp)**: L-shaped house using utility functions
- **Integration**: Uses `buildExtrudedIndexed()` from Utils.cpp
- **Geometry**: More complex footprint than House1

#### 📁 **[src/objects/houses/house-3/House3.cpp](src/objects/houses/house-3/House3.cpp)**

#### **Written by Me**

- **[Entire file](src/objects/houses/house-3/House3.cpp)**: Multi-story house variant
- **Features**: Different proportions and scaling from other house types

### 🌲 Trees

#### 📁 **[src/objects/tree/Tree.cpp](src/objects/tree/Tree.cpp)**

**🔗 Quick Links:**

- [Lines 1-50: Basic Structure](src/objects/tree/Tree.cpp#L1-L50)
- [Lines 51-100: Foliage Generation](src/objects/tree/Tree.cpp#L51-L100)
- [Lines 101-136: Trunk Geometry](src/objects/tree/Tree.cpp#L101-L136)

#### **Mixed Code (Written by Me + AI)**

- **[Lines 1-50](src/objects/tree/Tree.cpp#L1-L50)**: Started with cone-on-cylinder approach
- **[Lines 51-100](src/objects/tree/Tree.cpp#L51-L100)**: Irregular foliage generation (AI assisted)
- **[Lines 101-136](src/objects/tree/Tree.cpp#L101-L136)**: Trunk geometry (Hand-coded using Target.cpp as reference)

#### **Written by Me**

- Trunk cylinder geometry
- Tree scaling and variant system

#### **AI Generated**

- Irregular leaf/foliage patterns
- Advanced foliage layering

### 🎯 Targets

#### 📁 **[src/objects/targets/Target.cpp](src/objects/targets/Target.cpp)**

**🔗 Quick Links:**

- [Lines 1-50: Stand/Pole](src/objects/targets/Target.cpp#L1-L50)
- [Lines 51-150: Circular Board](src/objects/targets/Target.cpp#L51-L150)
- [Lines 151-193: Assembly](src/objects/targets/Target.cpp#L151-L193)

#### **Mixed Code (Written by Me + AI)**

- **[Lines 1-50](src/objects/targets/Target.cpp#L1-L50)**: Target stand/pole geometry (Written by Me)
- **[Lines 51-150](src/objects/targets/Target.cpp#L51-L150)**: Circular board with colored rings (AI Generated)
- **[Lines 151-193](src/objects/targets/Target.cpp#L151-L193)**: Assembly and positioning (Written by Me)

#### **Written by Me**

- Black pole/stand structure
- Target positioning and assembly

#### **AI Generated**

- Circular target board geometry
- Ring pattern and color calculations

---

## 🛠️ Utilities

### 📁 **[src/utils/Utils.cpp](src/utils/Utils.cpp)**

**🔗 Quick Links:**

- [Lines 1-57: buildExtrudedIndexed()](src/utils/Utils.cpp#L1-L57)

#### **Written by Me**

- **[Entire file](src/utils/Utils.cpp)**: Utility functions for 3D geometry extrusion
- **[Lines 1-57](src/utils/Utils.cpp#L1-L57)**: `buildExtrudedIndexed()` function for creating 3D prisms from 2D footprints
- **Reference**: Built using House1.cpp as reference
- **Future use**: Designed for cars, enemy hitboxes, and other box-shaped objects

---

## 🔧 Third-Party Libraries

### 📁 **[src/glad.c](src/glad.c)**

- **Status**: Third-party OpenGL loader library
- **Purpose**: OpenGL function loading

### 📁 **[src/KHR/khrplatform.h](src/KHR/khrplatform.h)**

- **Status**: Khronos platform definitions
- **Purpose**: Cross-platform OpenGL types

---

## 📊 Code Authorship Summary

### **Files Primarily Written by Me:**

- [`src/objects/land/Land.cpp`](src/objects/land/Land.cpp)
- [`src/objects/houses/house-2/House2.cpp`](src/objects/houses/house-2/House2.cpp)
- [`src/objects/houses/house-3/House3.cpp`](src/objects/houses/house-3/House3.cpp)
- [`src/utils/Utils.cpp`](src/utils/Utils.cpp)

### **Files with Mixed Authorship:**

- [`src/main.cpp`](src/main.cpp) - Core application logic with collision detection
- [`src/rendering/camera/Camera.cpp`](src/rendering/camera/Camera.cpp) - First-person camera system
- [`src/objects/houses/house-1/House1.cpp`](src/objects/houses/house-1/House1.cpp) - Basic house with manual geometry
- [`src/objects/tree/Tree.cpp`](src/objects/tree/Tree.cpp) - Procedural tree generation
- [`src/objects/targets/Target.cpp`](src/objects/targets/Target.cpp) - Target practice objects

### **Files Primarily AI Generated:**

- [`src/Shader.cpp`](src/Shader.cpp) - Standard OpenGL shader wrapper
- [`src/rendering/mesh/Mesh.cpp`](src/rendering/mesh/Mesh.cpp) - Mesh rendering utilities

---

## 🚀 GitHub Navigation Features

### **File Navigation:**

- Click any file path to view the file on GitHub
- All paths are relative to your repository root

### **Line Navigation:**

- Click line range links (e.g., `#L1-L10`) to jump to specific code sections
- Perfect for code reviews and documentation

### **Function Navigation:**

- Use Quick Links sections to navigate directly to function implementations
- Organized by logical code sections

### **Usage:**

1. **View Files**: Click any `[filename.cpp](src/path/file.cpp)` to open on GitHub
2. **Jump to Code**: Click line links like `[Lines X-Y](src/file.cpp#LX-LY)` to see exact code
3. **Navigate Sections**: Use the Quick Navigation menu to jump between components
4. **Code Reviews**: Perfect for linking to specific functions during reviews

---

## 📝 Notes

1. **Excluded Files**: `glad.c`, files in `glad/` and `KHR/` folders are third-party libraries
2. **Reference Materials**: learnopengl.com used as primary educational resource and Github Projects
3. **Development Style**: Hand-coded geometry construction with selective AI assistance for complex mathematical operations
4. **Future Plans**: Utils.cpp designed for extensibility to support additional object types
5. **GitHub Integration**: All links work directly in GitHub repository view

---

## 🔄 Last Updated

_Document last updated with GitHub navigation features_
