#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    GLuint GetProgramID();
    void SetInteger(const std::string &name, int value);
    void SetVector3(const std::string &name, const glm::vec3 &vec3);
    void SetMatrix4(const std::string &name, const glm::mat4 &mat4);

private:
    GLuint _id;

    GLuint CompileShader(GLenum shaderType, const std::string &shaderSource);
};