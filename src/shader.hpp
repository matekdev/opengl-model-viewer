#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    GLuint GetProgramID();
    void SetInteger(const std::string &name, int value);

private:
    GLuint _id;

    GLuint CompileShader(GLenum shaderType, const std::string &shaderSource);
};