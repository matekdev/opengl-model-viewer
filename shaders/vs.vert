#version 330 core

layout (location = 0) in vec3 vertexPosition;
uniform mat4 camMatrix;
varying vec4 fragmentColor;

void main()
{
	gl_Position = camMatrix * vec4(vertexPosition, 1.0);
    fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
}
