#include "camera.hpp"

Camera::Camera()
{
    Reset();
    UpdateViewMatrix();
}

void Camera::Reset()
{
    Distance = 2.0f;
    _pitch = 0.0f;
    _yaw = 0.0f;
    Position = glm::vec3(0.0f, 0.0f, Distance);
    FocusPoint = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Camera::SetAspect(float aspect)
{
    _projectionMatrix = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
}

void Camera::Update(Shader *shader)
{
    if (RotationSpeed > 0)
        _yaw += RotationSpeed * 0.01f;

    UpdateViewMatrix();

    glm::mat4 model{1.0f};
    shader->SetMatrix4("model", model);
    shader->SetMatrix4("view", _viewMatrix);
    shader->SetMatrix4("projection", _projectionMatrix);
}

void Camera::OnScroll(double delta)
{
    Distance += -delta * 0.3f;
    Distance = std::max(Distance, 0.0f);
}

void Camera::OnMouseMove(double x, double y, bool isWindowFocused, Input::Button buttonPressed)
{
    glm::vec2 mousePos{x, y};
    glm::vec2 delta = (mousePos - _currentMousePos) * 0.004f;

    if (buttonPressed == Input::Left && isWindowFocused)
    {
        auto up = glm::rotate(GetDirection(), _up);
        float sign = up.y < 0 ? -1.0f : 1.0f;
        _yaw += sign * delta.x * ROTATION_SPEED;
        _pitch += delta.y * ROTATION_SPEED;
    }
    else if (buttonPressed == Input::Middle && isWindowFocused)
    {
        glm::vec2 delta = (mousePos - _currentMousePos) * 0.003f;

        FocusPoint += -glm::rotate(GetDirection(), _right) * delta.x * Distance;
        FocusPoint += glm::rotate(GetDirection(), _up) * delta.y * Distance;
    }

    _currentMousePos = mousePos;
}

void Camera::UpdateViewMatrix()
{
    Position = FocusPoint - GetForward() * Distance;

    glm::quat orientation = GetDirection();
    _viewMatrix = glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(orientation);
    _viewMatrix = glm::inverse(_viewMatrix);
}

glm::quat Camera::GetDirection()
{
    return glm::quat(glm::vec3(-_pitch, -_yaw, 0.0f));
}

glm::vec3 Camera::GetForward()
{
    return glm::rotate(GetDirection(), _forward);
}
