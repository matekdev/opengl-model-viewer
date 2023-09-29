#include "camera.hpp"

Camera::Camera()
{
    Reset();
    UpdateViewMatrix();
}

void Camera::Reset()
{
    _distance = 2.0f;
    _pitch = 0.0f;
    _yaw = 0.0f;
    _position = glm::vec3(0.0f, 0.0f, _distance);
    _focusPoint = glm::vec3(0.0f, 0.0f, 0.0f);
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
    _distance += -delta * 0.3f;
}

void Camera::OnMouseMove(double x, double y, bool isLeftMouseButtonDown)
{
    glm::vec2 mousePos{x, y};
    glm::vec2 delta = (mousePos - _currentMousePos) * 0.004f;

    if (isLeftMouseButtonDown)
    {
        auto up = glm::rotate(GetDirection(), _up);
        float sign = up.y < 0 ? -1.0f : 1.0f;
        _yaw += sign * delta.x * ROTATION_SPEED;
        _pitch += delta.y * ROTATION_SPEED;
    }

    _currentMousePos = mousePos;
}

void Camera::UpdateViewMatrix()
{
    _position = _focusPoint - GetForward() * _distance;

    glm::quat orientation = GetDirection();
    _viewMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(orientation);
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
