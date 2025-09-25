// AI Generated Code

// Fragment shader: takes the color from the vertex shader and outputs it to the screen.
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}