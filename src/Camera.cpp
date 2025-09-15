#include "Camera.h"

Camera::Camera(glm::vec3 startPos)
    : Position(startPos), Yaw(-90.0f), Pitch(0.0f), Speed(5.0f) {}

glm::mat4 Camera::GetViewMatrix() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front = glm::normalize(front);
    return glm::lookAt(Position, Position + front, glm::vec3(0,1,0));
}

void Camera::ProcessKeyboard(float df, float dr, float du) {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front = glm::normalize(front);
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));
    glm::vec3 up = glm::normalize(glm::cross(right, front));

    Position += front * df * Speed * 0.016f;
    Position += right * dr * Speed * 0.016f;
    Position += up * du * Speed * 0.016f;
}

void Camera::ProcessMouse(float xoffset, float yoffset) {
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    Yaw += xoffset;
    Pitch += yoffset;
    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;
}
