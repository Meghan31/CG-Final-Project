// GLAD loads modern OpenGL function pointers (needed before calling OpenGL)
#include <glad/glad.h>
// GLFW creates the window and handles input (keyboard + mouse)
#include <GLFW/glfw3.h>
// GLM: math library for vectors, matrices, and transforms
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "Shader.h"
#include "rendering/camera/Camera.h"
#include "rendering/mesh/Mesh.h"

// object headers
#include "objects/land/Land.h"
#include "objects/houses/house-1/House1.h"
#include "objects/houses/house-2/House2.h" 
#include "objects/houses/house-3/House3.h"
#include "objects/tree/Tree.h"
#include "objects/targets/Target.h"

using namespace std;

// Forward declarations so main can call these helpers
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
bool isPositionValid(glm::vec3 pos, const vector<glm::vec3>& existingPositions, float minDistance);
glm::vec3 getRandomPosition(mt19937& gen, uniform_real_distribution<float>& dist, 
                          const vector<glm::vec3>& existingPositions, float minDistance);
bool checkCollision(glm::vec3 newPos, glm::vec3 objPos, float radius);
bool checkAllCollisions(glm::vec3 newPos);
glm::vec3 findSafeSpawnPosition();

// Window size (1280 x 720)
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// Scene bounds (larger play area to explore)
const float SCENE_SIZE = 120.0f;
// const float MIN_DISTANCE = 5.0f;

// Different spacing per object type for a natural layout
const float HOUSE_MIN_DISTANCE = 15.0f;   // Houses far apart - spacious neighborhoods
const float TREE_MIN_DISTANCE = 8.0f;     // Trees medium spacing - natural forest feel  
const float TARGET_MIN_DISTANCE = 4.0f;   // Targets close together - easy to find

// Camera (acts like the player in first-person)
Camera camera(glm::vec3(0.0f, 1.8f, 0.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Mouse state: track last position to compute movement offsets
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Instance structure for objects (each item in the world has a position/scale/rotation)
struct Instance {
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    glm::vec3 color1;  // Wall color for houses, trunk color for trees
    glm::vec3 color2;  // Roof color for houses, leaf color for trees
    int type;          // House type (1 or 3 only - 2 removed)
    float collisionRadius; // Collision radius for this object
};

// Global vectors used for collision checks (filled during setup)
vector<Instance> houses;
vector<Instance> trees;
vector<Instance> targets;

int main() {
    // Initialize GLFW and request an OpenGL 3.3 Core profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS for core profile
#endif

    // Create the window and OpenGL context. If this fails, exit.
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Meghasrivardhan Pulakhandam - HW3", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Update the viewport when the window resizes
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Capture the mouse so it controls the camera (first-person look)
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load OpenGL function pointers with GLAD (must happen after making the context current)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Enable depth testing so nearer objects occlude farther ones
    glEnable(GL_DEPTH_TEST);

    // Load/compile the shader program (vertex + fragment)
    Shader shader("shaders/basic.vert", "shaders/basic.frag");
    
    // Create the ground mesh (flat plane)
    Mesh landMesh = createGround();

    // Random number generation (makes the world feel a bit different each run)
    random_device rd;
    mt19937 gen(rd());
    
    // Use different distributions: houses far apart, trees moderately spaced, targets closer
    uniform_real_distribution<float> housePosDistFar(-SCENE_SIZE/2 + 10, SCENE_SIZE/2 - 10);     // Houses spread out
    uniform_real_distribution<float> treePosDistMed(-SCENE_SIZE/2 + 5, SCENE_SIZE/2 - 5);        // Trees medium spacing
    uniform_real_distribution<float> targetPosDistNear(-SCENE_SIZE/2 + 2, SCENE_SIZE/2 - 2);     // Targets close spacing
    
    uniform_real_distribution<float> scaleDist(0.8f, 1.3f);
    uniform_real_distribution<float> rotDist(0.0f, 360.0f);
    
    // Use house types 1, 2, and 3 (House2 is a simple cabin)
    vector<int> availableHouseTypes = {1, 2, 3};  // All types including simple cabin
    uniform_int_distribution<int> houseTypeIndexDist(0, 2);  // Random index for all types

    // Track used positions to avoid placing objects too close
    vector<glm::vec3> occupiedPositions;

    // Create house instances with larger spacing (spacious neighborhoods)
    houses.resize(8);  // Keep same number of houses
    vector<glm::vec3> wallColors = {
        {0.9f, 0.9f, 0.8f},   // Off-white
        {0.8f, 0.7f, 0.6f},   // Beige  
        {0.7f, 0.8f, 0.9f},   // Light blue
        {0.9f, 0.8f, 0.7f},   // Peach
        {0.6f, 0.8f, 0.6f},   // Light green
        {0.9f, 0.7f, 0.8f},   // Pink
        {0.8f, 0.8f, 0.9f},   // Lavender
        {0.9f, 0.9f, 0.7f}    // Light yellow
    };
    
    vector<glm::vec3> roofColors = {
        {0.6f, 0.3f, 0.2f},   // Dark red
        {0.4f, 0.3f, 0.2f},   // Dark brown
        {0.3f, 0.4f, 0.3f},   // Dark green
        {0.5f, 0.4f, 0.3f},   // Tan
        {0.4f, 0.4f, 0.5f},   // Dark blue
        {0.5f, 0.3f, 0.4f},   // Maroon
        {0.3f, 0.3f, 0.4f},   // Dark purple
        {0.6f, 0.5f, 0.2f}    // Golden brown
    };
    
    for (int i = 0; i < 8; ++i) {
        // Pick a random position that isn't too close to existing objects
        houses[i].position = getRandomPosition(gen, housePosDistFar, occupiedPositions, HOUSE_MIN_DISTANCE);
        occupiedPositions.push_back(houses[i].position);
        
        houses[i].scale = glm::vec3(scaleDist(gen));
        houses[i].rotation = rotDist(gen);
        houses[i].color1 = wallColors[i];
        houses[i].color2 = roofColors[i];
        houses[i].type = availableHouseTypes[houseTypeIndexDist(gen)];  // All types 1, 2, 3
        houses[i].collisionRadius = 4.0f * houses[i].scale.x; // simple sphere-like collision size
    }
    
    // Create tree instances with medium spacing (forest clusters)
    trees.resize(12);  // More trees for bigger area
    vector<glm::vec3> leafColors = {
        {0.0f, 0.6f, 0.0f},   // Dark green
        {0.1f, 0.7f, 0.1f},   // Medium green
        {0.2f, 0.8f, 0.1f},   // Bright green
        {0.0f, 0.5f, 0.2f},   // Forest green
        {0.1f, 0.6f, 0.0f},   // Pine green
        {0.0f, 0.7f, 0.2f},   // Spring green
        {0.2f, 0.6f, 0.0f},   // Olive green
        {0.0f, 0.8f, 0.1f},   // Lime green
        {0.1f, 0.5f, 0.1f},   // Deep forest
        {0.3f, 0.7f, 0.2f},   // Light green
        {0.0f, 0.6f, 0.3f},   // Emerald
        {0.2f, 0.5f, 0.0f}    // Army green
    };
    
    for (int i = 0; i < 12; ++i) {
        // Random positions with a different minimum distance for trees
        trees[i].position = getRandomPosition(gen, treePosDistMed, occupiedPositions, TREE_MIN_DISTANCE);
        occupiedPositions.push_back(trees[i].position);
        
        float heightScale = scaleDist(gen);
        float foliageScale = uniform_real_distribution<float>(0.7f, 1.2f)(gen);
        trees[i].scale = glm::vec3(heightScale, heightScale, foliageScale); // Z component affects leaf size
        trees[i].rotation = rotDist(gen);
        trees[i].color1 = glm::vec3(0.4f, 0.25f, 0.1f); // Trunk color
        trees[i].color2 = leafColors[i % leafColors.size()];
        trees[i].type = 0; // All trees use same base type
        trees[i].collisionRadius = 2.5f * trees[i].scale.x;
    }
    
    // Create target instances with closer spacing (easier to find)
    targets.resize(15);  // Many more targets for bigger area and easier gameplay
    for (int i = 0; i < 15; ++i) {
        // Targets are smaller and can be closer to each other
        targets[i].position = getRandomPosition(gen, targetPosDistNear, occupiedPositions, TARGET_MIN_DISTANCE);
        occupiedPositions.push_back(targets[i].position);
        
        targets[i].scale = glm::vec3(uniform_real_distribution<float>(0.9f, 1.1f)(gen));
        targets[i].rotation = rotDist(gen);
        targets[i].color1 = glm::vec3(1.0f); // Not used for targets
        targets[i].color2 = glm::vec3(1.0f); // Not used for targets
        targets[i].type = 0;
        targets[i].collisionRadius = 1.2f * targets[i].scale.x; // small hit area
    }

    // Set camera to a safe spawn position (avoid spawning inside objects)
    camera.Position = findSafeSpawnPosition();

    cout << "\n\n\n🏘️  SHOOTING TOWN CREATED! 🏘️" << endl;
    cout << "- " << houses.size() << " houses (spacious neighborhoods) 🏠" << endl;
    cout << "- " << trees.size() << " trees (forest clusters) 🌲" << endl;
    cout << "- " << targets.size() << " targets (treasure hunt!) 🎯" << endl;

    cout << "\nControls:" << endl;
    cout << "- WASD: Move around (with collision detection)" << endl;
    cout << "- Mouse: Look around" << endl;
    cout << "- ESC: Exit" << endl;
    cout << "\nPlayer spawned at safe location: (" << camera.Position.x << ", " << camera.Position.z << ")" << endl;

    // Main render loop (runs until the window is closed)
    while (!glfwWindowShouldClose(window)) {
        // Compute deltaTime (time between frames) for smooth movement
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle keyboard inputs to move the camera
        processInput(window);

        // Clear the screen each frame (color + depth)
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f); // Sky blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program for the draws below
        shader.use();

        // Set projection and view matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                                (float)SCR_WIDTH / (float)SCR_HEIGHT,
                                                0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Draw ground (model is identity since it's already at origin)
        shader.setMat4("model", glm::mat4(1.0f));
        landMesh.Draw();

        // Draw houses. Model matrix order: translate -> rotate -> scale
        for (const auto& house : houses) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, house.position);
            model = glm::rotate(model, glm::radians(house.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, house.scale);
            shader.setMat4("model", model);
            
            // Choose the house mesh based on type
            Mesh houseMesh = [&]() -> Mesh {
                switch (house.type) {
                    case 1:
                        return createHouse1(house.color1, house.color2);
                    case 2:  // Simple cabin house
                        return createHouse2(house.color1, house.color2);
                    case 3:
                        return createHouse3(house.color1, house.color2);
                    default:
                        return Mesh(std::vector<Vertex>(), std::vector<unsigned int>());
                }
            }();
            
            houseMesh.Draw();
        }

        // Draw trees
        for (const auto& tree : trees) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, tree.position);
            model = glm::rotate(model, glm::radians(tree.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, tree.scale);
            shader.setMat4("model", model);
            
            Mesh treeMesh = createTreeVariant(tree.scale.x, tree.scale.z, tree.color2);
            treeMesh.Draw();
        }

        // Draw targets (smaller objects scattered around the town)
        for (const auto& target : targets) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, target.position);
            model = glm::rotate(model, glm::radians(target.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, target.scale);
            shader.setMat4("model", model);
            
            Mesh targetMesh = createTarget();
            targetMesh.Draw();
        }

        // Show the rendered frame and process OS events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Store current position to revert if a collision happens
    glm::vec3 oldPosition = camera.Position;

    // Camera movement with collision detection on the XZ plane
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
        if (checkAllCollisions(camera.Position)) {
            camera.Position = oldPosition; // Revert if collision detected
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (checkAllCollisions(camera.Position)) {
            camera.Position = oldPosition; // Revert if collision detected
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
        if (checkAllCollisions(camera.Position)) {
            camera.Position = oldPosition; // Revert if collision detected
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
        if (checkAllCollisions(camera.Position)) {
            camera.Position = oldPosition; // Revert if collision detected
        }
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
        // No collision check for vertical movement
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
        // No collision check for vertical movement
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window; // Unused parameter
    // Update the OpenGL viewport so rendering matches the new window size
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    (void)window; // Unused parameter
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    // Pass mouse movement offsets to the camera to look around
    camera.ProcessMouseMovement(xoffset, yoffset);
}

bool isPositionValid(glm::vec3 pos, const vector<glm::vec3>& existingPositions, float minDistance) {
    // Check if this position is at least "minDistance" away from all other used positions
    for (const auto& existing : existingPositions) {
        if (glm::distance(pos, existing) < minDistance) {
            return false;
        }
    }
    return true;
}

glm::vec3 getRandomPosition(mt19937& gen, uniform_real_distribution<float>& dist, 
                          const vector<glm::vec3>& existingPositions, float minDistance) {
    // Try up to 100 times to find a valid random position (then expand the search area as a fallback)
    glm::vec3 pos;
    int attempts = 0;
    do {
        pos = glm::vec3(dist(gen), 0.0f, dist(gen));
        attempts++;
        if (attempts > 100) {
            // Fallback: expand search area
            uniform_real_distribution<float> expandedDist(-SCENE_SIZE/2, SCENE_SIZE/2);
            pos = glm::vec3(expandedDist(gen), 0.0f, expandedDist(gen));
            break;
        }
    } while (!isPositionValid(pos, existingPositions, minDistance));
    return pos;
}

bool checkCollision(glm::vec3 newPos, glm::vec3 objPos, float radius) {
    // Simple 2D (XZ plane) distance check — I treat each object like a circle for collision
    float distance = sqrt((newPos.x - objPos.x) * (newPos.x - objPos.x) + 
                         (newPos.z - objPos.z) * (newPos.z - objPos.z));
    return distance < radius;
}

bool checkAllCollisions(glm::vec3 newPos) {
    // Check collision with all houses
    for (const auto& house : houses) {
        if (checkCollision(newPos, house.position, house.collisionRadius)) {
            return true;
        }
    }
    
    // Check collision with all trees
    for (const auto& tree : trees) {
        if (checkCollision(newPos, tree.position, tree.collisionRadius)) {
            return true;
        }
    }
    
    // Check collision with all targets
    for (const auto& target : targets) {
        if (checkCollision(newPos, target.position, target.collisionRadius)) {
            return true;
        }
    }
    
    // Check bounds of the scene (keeps the player inside the square world)
    if (abs(newPos.x) > SCENE_SIZE/2 || abs(newPos.z) > SCENE_SIZE/2) {
        return true;
    }
    
    return false;
}

glm::vec3 findSafeSpawnPosition() {
    // Prefer spawning near the edges where there are usually fewer objects (safer start)
    vector<glm::vec3> edgePositions = {
        {-SCENE_SIZE/2 + 2, 1.8f, 0},           // Left edge
        {SCENE_SIZE/2 - 2, 1.8f, 0},            // Right edge  
        {0, 1.8f, -SCENE_SIZE/2 + 2},           // Front edge
        {0, 1.8f, SCENE_SIZE/2 - 2},            // Back edge
        {-SCENE_SIZE/2 + 2, 1.8f, -SCENE_SIZE/2 + 2},  // Corner
        {SCENE_SIZE/2 - 2, 1.8f, -SCENE_SIZE/2 + 2},   // Corner
        {-SCENE_SIZE/2 + 2, 1.8f, SCENE_SIZE/2 - 2},   // Corner
        {SCENE_SIZE/2 - 2, 1.8f, SCENE_SIZE/2 - 2}     // Corner
    };
    
    // Try each edge position and return the first that doesn't collide with anything
    for (const auto& pos : edgePositions) {
        if (!checkAllCollisions(pos)) {
            return pos;
        }
    }
    
    // If no edge position is safe, try a simple fallback near the front edge
    return glm::vec3(0, 1.8f, -SCENE_SIZE/2 + 1);
}