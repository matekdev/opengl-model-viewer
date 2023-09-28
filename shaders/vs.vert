#version 330 core

layout (location = 0) in vec3 vertexPosition;

varying vec4 fragmentColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 WorldPos;

void main()
{
    WorldPos = vec3(model * vec4(vertexPosition, 1.0));
    fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
}
