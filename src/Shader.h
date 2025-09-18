// Simple wrapper around an OpenGL shader program.
// I load GLSL files, compile+link them, and then set uniforms from C++.
#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID; // OpenGL program handle
    Shader(const char* vertexPath, const char* fragmentPath); // builds the program
    void use(); // tell OpenGL to use this program
    void setMat4(const std::string &name, const glm::mat4 &mat) const; // upload mat4 uniform
    void setVec3(const std::string &name, const glm::vec3 &val) const; // upload vec3 uniform
};
