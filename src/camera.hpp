#pragma once

#include "shader.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
    Camera();
    void SetAspect(float aspect);
    void Update(Shader *shader);
    void OnScroll(double delta);
    void OnMouseMove(double x, double y, bool isLeftMouseButtonDown);

private:
    const float ROTATION_SPEED = 2.0f;
    const glm::vec3 _forward = {0.0f, 0.0f, -1.0f};
    const glm::vec3 _up = {0.0f, 1.0f, 0.0f};

    glm::vec3 _position;
    glm::vec3 _focusPoint;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

    float _distance = 2.0f;
    float _pitch = 0.0f;
    float _yaw = 0.0f;
    glm::vec2 _currentMousePos = {0.0f, 0.0f};

    void UpdateViewMatrix();
    glm::quat GetDirection();
    glm::vec3 GetForward();
};
