#pragma once

#include "shader.hpp"
#include "input.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
    float RotationSpeed = 0.0f;

    Camera();
    void Reset();
    void SetAspect(float aspect);
    void Update(Shader *shader);
    void OnScroll(double delta);
    void OnMouseMove(double x, double y, Input::Button buttonPressed);

private:
    const float ROTATION_SPEED = 2.0f;
    const glm::vec3 _forward = {0.0f, 0.0f, -1.0f};
    const glm::vec3 _up = {0.0f, 1.0f, 0.0f};
    const glm::vec3 _right = {1.0f, 0.0f, 0.0f};

    glm::vec3 _position;
    glm::vec3 _focusPoint;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

    float _distance;
    float _pitch;
    float _yaw;
    glm::vec2 _currentMousePos = {0.0f, 0.0f};

    void UpdateViewMatrix();
    glm::quat GetDirection();
    glm::vec3 GetForward();
};
