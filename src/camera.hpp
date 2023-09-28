#pragma once

#include "shader.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
    Camera(float width, float height);
    void SetAspect(float aspect);
    void Update(Shader *shader);

private:
    const glm::vec3 _forward = {0.0f, 0.0f, -1.0f};
    const glm::vec3 _up = {0.0f, 1.0f, 0.0f};

    glm::vec3 _position;
    glm::vec3 _focusPoint;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

    float _distance = 2.0f;
    float _pitch = 0.0f;
    float _yaw = 0.0f;

    void UpdateViewMatrix();
    glm::quat GetDirection();
    glm::vec3 GetForward();
};
