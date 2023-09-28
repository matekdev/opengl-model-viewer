#include "camera.hpp"

Camera::Camera(float width, float height)
{
    _position = glm::vec3(0.0f, 0.0f, _distance);
    _focusPoint = glm::vec3(0.0f, 0.0f, 0.0f);

    SetAspect(width / height);
    UpdateViewMatrix();
}

void Camera::SetAspect(float aspect)
{
    _projectionMatrix = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
}

void Camera::Update(Shader *shader)
{
    glm::mat4 model{1.0f};
    shader->SetMatrix4("model", model);
    shader->SetMatrix4("view", _viewMatrix);
    shader->SetMatrix4("projection", _projectionMatrix);
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
