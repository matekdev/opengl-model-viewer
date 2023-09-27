#include "opengl_context.hpp"

OpenGLContext::OpenGLContext(int width, int height, const std::string &windowName) : _width(width), _height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (!_window)
        throw std::runtime_error("Failed to create GLFW window.");

    glfwMakeContextCurrent(_window);
    gladLoadGL();
    glfwSetWindowUserPointer(_window, this);

    _shader = std::make_unique<Shader>("shaders/vs.vert", "shaders/fs.frag");
    _panel = std::make_unique<UIPanel>(_window);
}

OpenGLContext::~OpenGLContext()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void OpenGLContext::Run()
{
    while (!glfwWindowShouldClose(_window))
    {
        PreRender();
        _panel->PreRender();

        // TODO: Probably move this somewhere else, who knows!
        glUseProgram(_shader->GetProgramID());

        _panel->Render();

        _panel->PostRender();
        PostRender();
    }
}

void OpenGLContext::PreRender()
{
    glViewport(0, 0, _width, _height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::PostRender()
{
    glfwPollEvents();
    glfwSwapBuffers(_window);
}