// Satnderd Boiler plate code used learnopengl.com and AI to Generate Code (changed very few parts of it)

// Standard Camera class for 3D navigation, Changed it according to my needs as a first-person controller 
// Used FPP rules for movement and mouse look

// Simple first-person style camera. I keep y at eye height and move on the XZ plane.
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
using namespace std;

Camera::Camera(glm::vec3 startPos)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(5.0f),
      MouseSensitivity(0.1f),
      Zoom(45.0f)
{
    Position = startPos;
    Position.y = 1.8f; // keep the camera at eye level
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = -90.0f;
    Pitch = 0.0f;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    // View matrix looks from my position towards where I'm facing
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * (deltaTime > 0.0f ? deltaTime : 0.016f); // fallback for zero dt
    
    if (direction == FORWARD) {
    // Move forward but only on XZ plane (no sliding up/down when looking up)
        glm::vec3 frontXZ = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));
        Position += frontXZ * velocity;
    }
    if (direction == BACKWARD) {
        glm::vec3 frontXZ = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));
        Position -= frontXZ * velocity;
    }
    if (direction == LEFT) {
        glm::vec3 rightXZ = glm::normalize(glm::vec3(Right.x, 0.0f, Right.z));
        Position -= rightXZ * velocity;
    }
    if (direction == RIGHT) {
        glm::vec3 rightXZ = glm::normalize(glm::vec3(Right.x, 0.0f, Right.z));
        Position += rightXZ * velocity;
    }
    if (direction == UP) {
        Position += WorldUp * velocity;
    }
    if (direction == DOWN) {
        Position -= WorldUp * velocity;
    }
    
    // Always keep height fixed so I walk like a person
    Position.y = 1.8f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset; // scroll zooms the camera in/out (change FOV)
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 90.0f) Zoom = 90.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}