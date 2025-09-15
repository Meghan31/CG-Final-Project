#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 Position;
    float Yaw, Pitch;
    float Speed;

    Camera(glm::vec3 startPos);

    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(float deltaForward, float deltaRight, float deltaUp);
    void ProcessMouse(float xoffset, float yoffset);
};
