#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"
#include "Shader.h"
#include "Objects.h"

Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));
float lastX=400, lastY=300;
bool firstMouse=true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) { lastX=xpos; lastY=ypos; firstMouse=false; }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX=xpos; lastY=ypos;
    camera.ProcessMouse(xoffset,yoffset);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"MyTown",NULL,NULL);
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/basic.vert","shaders/basic.frag");

    Mesh house = createHouse();
    Mesh tree = createTree();
    Mesh target = createTarget();

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Keyboard
        float df=0,dr=0,du=0;
        if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS) df+=1;
        if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS) df-=1;
        if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS) dr-=1;
        if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS) dr+=1;
        if(glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS) du+=1;
        if(glfwGetKey(window,GLFW_KEY_E)==GLFW_PRESS) du-=1;
        camera.ProcessKeyboard(df,dr,du);

        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f/600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection",projection);
        shader.setMat4("view",view);

        // Draw house at different places
        for(int i=0;i<3;i++){
            glm::mat4 model=glm::translate(glm::mat4(1.0f),glm::vec3(i*3.0f,0,0));
            shader.setMat4("model",model);
            shader.setVec3("inColor",glm::vec3(1.0f,0.0f,0.0f));
            house.Draw();
        }

        glm::mat4 model=glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5));
        shader.setMat4("model",model);
        shader.setVec3("inColor",glm::vec3(0.0f,1.0f,0.0f));
        tree.Draw();

        glm::mat4 model2=glm::translate(glm::mat4(1.0f),glm::vec3(5,0,-5));
        shader.setMat4("model",model2);
        shader.setVec3("inColor",glm::vec3(0.0f,0.0f,1.0f));
        target.Draw();

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
