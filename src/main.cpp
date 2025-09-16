#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <random>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

// object headers
#include "objects/Land.h"
#include "objects/House.h"
#include "objects/Tree.h"
#include "objects/Target.h"

using namespace std;

// Function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
bool isPositionValid(glm::vec3 pos, const vector<glm::vec3>& existingPositions, float minDistance);
glm::vec3 getRandomPosition(mt19937& gen, uniform_real_distribution<float>& dist, 
                          const vector<glm::vec3>& existingPositions, float minDistance);

// Settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// Scene bounds
const float SCENE_SIZE = 40.0f;
const float MIN_DISTANCE = 3.0f;

// Camera
Camera camera(glm::vec3(0.0f, 1.8f, 0.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Instance structure for objects
struct Instance {
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    glm::vec3 color1;  // Wall color for houses, trunk color for trees
    glm::vec3 color2;  // Roof color for houses, leaf color for trees
    int type;          // Variant type
};

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Town - 3D Scene", NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    // Capture mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // Create base meshes
    Mesh landMesh = createGround();
    
    // Random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> posDist(-SCENE_SIZE/2, SCENE_SIZE/2);
    uniform_real_distribution<float> scaleDist(0.8f, 1.3f);
    uniform_real_distribution<float> rotDist(0.0f, 360.0f);
    uniform_real_distribution<float> colorDist(0.0f, 1.0f);
    uniform_int_distribution<int> typeDist(0, 2);
    
    vector<glm::vec3> occupiedPositions;
    
    // Create house instances
    vector<Instance> houses(5);
    vector<glm::vec3> wallColors = {
        {0.9f, 0.9f, 0.9f},   // White
        {0.8f, 0.8f, 0.7f},   // Cream
        {0.7f, 0.8f, 0.9f},   // Light blue
        {0.9f, 0.8f, 0.7f},   // Peach
        {0.8f, 0.9f, 0.8f}    // Light green
    };
    vector<glm::vec3> roofColors = {
        {0.7f, 0.3f, 0.3f},   // Red
        {0.3f, 0.5f, 0.7f},   // Blue
        {0.4f, 0.6f, 0.3f},   // Green
        {0.6f, 0.4f, 0.8f},   // Purple
        {0.8f, 0.5f, 0.2f}    // Orange
    };
    
    for (int i = 0; i < 5; ++i) {
        houses[i].position = getRandomPosition(gen, posDist, occupiedPositions, MIN_DISTANCE);
        occupiedPositions.push_back(houses[i].position);
        
        houses[i].scale = glm::vec3(scaleDist(gen));
        houses[i].rotation = rotDist(gen);
        houses[i].color1 = wallColors[i];
        houses[i].color2 = roofColors[i];
        houses[i].type = typeDist(gen);
    }
    
    // Create tree instances
    vector<Instance> trees(8);
    vector<glm::vec3> leafColors = {
        {0.0f, 0.6f, 0.0f},   // Dark green
        {0.1f, 0.7f, 0.1f},   // Medium green
        {0.2f, 0.8f, 0.1f},   // Bright green
        {0.0f, 0.5f, 0.2f},   // Forest green
        {0.1f, 0.6f, 0.0f},   // Pine green
        {0.0f, 0.7f, 0.2f},   // Spring green
        {0.2f, 0.6f, 0.0f},   // Olive green
        {0.0f, 0.8f, 0.1f}    // Lime green
    };
    
    for (int i = 0; i < 8; ++i) {
        trees[i].position = getRandomPosition(gen, posDist, occupiedPositions, MIN_DISTANCE);
        occupiedPositions.push_back(trees[i].position);
        
        float heightScale = scaleDist(gen);
        float foliageScale = uniform_real_distribution<float>(0.7f, 1.2f)(gen);
        trees[i].scale = glm::vec3(heightScale, heightScale, foliageScale);
        trees[i].rotation = rotDist(gen);
        trees[i].color1 = glm::vec3(0.4f, 0.25f, 0.1f); // Trunk color
        trees[i].color2 = leafColors[i];
        trees[i].type = 0; // All trees use same base type
    }
    
    // Create target instances  
    vector<Instance> targets(10);
    for (int i = 0; i < 10; ++i) {
        targets[i].position = getRandomPosition(gen, posDist, occupiedPositions, MIN_DISTANCE);
        occupiedPositions.push_back(targets[i].position);
        
        targets[i].scale = glm::vec3(uniform_real_distribution<float>(0.9f, 1.1f)(gen));
        targets[i].rotation = rotDist(gen);
        targets[i].color1 = glm::vec3(1.0f); // Not used for targets
        targets[i].color2 = glm::vec3(1.0f); // Not used for targets
        targets[i].type = 0;
    }

    cout << "Scene created with:" << endl;
    cout << "- " << houses.size() << " houses" << endl;
    cout << "- " << trees.size() << " trees" << endl;
    cout << "- " << targets.size() << " targets" << endl;
    cout << "\nControls:" << endl;
    cout << "- WASD: Move around" << endl;
    cout << "- Mouse: Look around" << endl;
    cout << "- ESC: Exit" << endl;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.5f, 0.7f, 1.0f, 1.0f); // Sky blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                                (float)SCR_WIDTH / (float)SCR_HEIGHT,
                                                0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Draw ground
        shader.setMat4("model", glm::mat4(1.0f));
        landMesh.Draw();

        // Draw all houses
        for (const auto& house : houses) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, house.position);
            model = glm::rotate(model, glm::radians(house.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, house.scale);
            shader.setMat4("model", model);
            
            Mesh houseMesh = createHouseVariant(house.type, house.color1, house.color2);
            houseMesh.Draw();
        }

        // Draw all trees
        for (const auto& tree : trees) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, tree.position);
            model = glm::rotate(model, glm::radians(tree.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, tree.scale);
            shader.setMat4("model", model);
            
            Mesh treeMesh = createTreeVariant(tree.scale.x, tree.scale.z, tree.color2);
            treeMesh.Draw();
        }

        // Draw all targets
        for (const auto& target : targets) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, target.position);
            model = glm::rotate(model, glm::radians(target.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, target.scale);
            shader.setMat4("model", model);
            
            Mesh targetMesh = createTarget();
            targetMesh.Draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow*, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

bool isPositionValid(glm::vec3 pos, const vector<glm::vec3>& existingPositions, float minDistance) {
    for (const auto& existing : existingPositions) {
        float distance = glm::length(pos - existing);
        if (distance < minDistance) {
            return false;
        }
    }
    return true;
}

glm::vec3 getRandomPosition(mt19937& gen, uniform_real_distribution<float>& dist, 
                          const vector<glm::vec3>& existingPositions, float minDistance) {
    glm::vec3 position;
    int attempts = 0;
    const int maxAttempts = 100;
    
    do {
        position = glm::vec3(dist(gen), 0.0f, dist(gen));
        attempts++;
    } while (!isPositionValid(position, existingPositions, minDistance) && attempts < maxAttempts);
    
    return position;
}