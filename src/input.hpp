#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Input
{
public:
    enum Button
    {
        None,
        Left,
        Right,
        Middle
    };

    static Button GetPressedButton(GLFWwindow *window);
};