#include "shader.hpp"

#include <fstream>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    std::ifstream is_vs(vertexShaderPath);
    const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

    std::ifstream is_fs(fragmentShaderPath);
    const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());

    _id = glCreateProgram();

    auto vs = CompileShader(GL_VERTEX_SHADER, f_vs);
    auto fs = CompileShader(GL_FRAGMENT_SHADER, f_fs);

    glAttachShader(_id, vs);
    glAttachShader(_id, fs);

    glLinkProgram(_id);
    glValidateProgram(_id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

GLuint Shader::GetProgramID()
{
    return _id;
}

void Shader::SetInteger(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::SetVector3(const std::string &name, const glm::vec3 &vec3)
{
    GLint myLoc = glGetUniformLocation(_id, name.c_str());
    glUniform3fv(myLoc, 1, glm::value_ptr(vec3));
}

void Shader::SetMatrix4(const std::string &name, const glm::mat4 &mat4)
{
    GLint myLoc = glGetUniformLocation(_id, name.c_str());
    glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
}

GLuint Shader::CompileShader(GLenum shaderType, const std::string &shaderSource)
{
    auto shaderId = glCreateShader(shaderType);

    const char *c_source = shaderSource.c_str();
    glShaderSource(shaderId, 1, &c_source, nullptr);
    glCompileShader(shaderId);

    GLint result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        GLchar *strInfoLog = new GLchar[length + 1];
        glGetShaderInfoLog(shaderId, length, &length, strInfoLog);

        fprintf(stderr, "Compile error in shader: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    return shaderId;
}