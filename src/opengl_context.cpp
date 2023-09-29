#include "opengl_context.hpp"

OpenGLContext::OpenGLContext(int width, int height, const std::string &windowName) : _width(width), _height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (!_window)
        throw std::runtime_error("Failed to create GLFW window.");

    glfwMakeContextCurrent(_window);
    gladLoadGL();
    glfwSetWindowUserPointer(_window, this);
    glfwSetScrollCallback(_window, OpenGLContext::OnScroll);
    glfwSwapInterval(0);

    _shader = std::make_unique<Shader>("shaders/vs.vert", "shaders/fs.frag");

    _uiContext = std::make_unique<UIContext>(_window);
    _scenePanel = std::make_unique<ScenePanel>(800, 600);
    _settingsPanel = std::make_unique<SettingsPanel>([this](const std::string &filePath)
                                                     { _scenePanel->LoadMesh(filePath); });
}

OpenGLContext::~OpenGLContext()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

Camera *OpenGLContext::GetCamera()
{
    return _scenePanel->GetCamera();
}

void OpenGLContext::Run()
{
    while (!glfwWindowShouldClose(_window))
    {
        PreRender();
        _uiContext->PreRender();

        glUseProgram(_shader->GetProgramID());

        _scenePanel->Render(_shader.get());
        _settingsPanel->Render(_scenePanel->GetCamera(), _scenePanel->GetModel(), _shader.get());

        _uiContext->PostRender();
        PostRender();
    }
}

void OpenGLContext::PreRender()
{
    glViewport(0, 0, _width, _height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::PostRender()
{
    glfwPollEvents();
    glfwSwapBuffers(_window);

    double x, y;
    glfwGetCursorPos(_window, &x, &y);

    GetCamera()->OnMouseMove(x, y, Input::GetPressedButton(_window));
}

void OpenGLContext::OnScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    auto glContext = static_cast<OpenGLContext *>(glfwGetWindowUserPointer(window));
    glContext->GetCamera()->OnScroll(yoffset);
}
