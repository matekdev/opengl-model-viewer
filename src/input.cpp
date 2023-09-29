#include "input.hpp"

Input::Button Input::GetPressedButton(GLFWwindow *window)
{
    if (glfwGetMouseButton(window, 0) == GLFW_PRESS)
        return Button::Left;
    else if (glfwGetMouseButton(window, 1) == GLFW_PRESS)
        return Button::Right;
    else if (glfwGetMouseButton(window, 2) == GLFW_PRESS)
        return Button::Middle;

    return Button::None;
}
