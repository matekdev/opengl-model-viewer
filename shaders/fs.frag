#version 330 core

uniform vec3 fragmentColor;

void main()
{
    gl_FragColor = vec4(fragmentColor, 1.0);
}
