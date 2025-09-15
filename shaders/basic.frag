#version 330 core
out vec4 FragColor;
in vec3 ourColor;
uniform vec3 inColor;
void main() {
    FragColor = vec4(ourColor * inColor,1.0);
}
