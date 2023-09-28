#include "opengl_context.hpp"

OpenGLContext::OpenGLContext(int width, int height, const std::string &windowName) : Width(width), Height(height)
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
    glfwSetWindowSizeCallback(_window, OpenGLContext::OnWindowResize);
    glfwSetScrollCallback(_window, OpenGLContext::OnScroll);

    _model = std::make_unique<Model>("models/stanford-bunny.obj");
    _shader = std::make_unique<Shader>("shaders/vs.vert", "shaders/fs.frag");
    _camera = std::make_unique<Camera>();
    _panel = std::make_unique<UIPanel>(_window);
}

OpenGLContext::~OpenGLContext()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

Camera *OpenGLContext::GetCamera()
{
    return _camera.get();
}

void OpenGLContext::Run()
{
    while (!glfwWindowShouldClose(_window))
    {
        PreRender();
        _panel->PreRender();

        glUseProgram(_shader->GetProgramID());

        _camera->SetAspect(Width / Height);
        _camera->Update(_shader.get());

        _model->Render(_shader.get());
        _panel->Render();

        _panel->PostRender();
        PostRender();
    }
}

void OpenGLContext::PreRender()
{
    glViewport(0, 0, Width, Height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::PostRender()
{
    glfwPollEvents();
    glfwSwapBuffers(_window);

    double x, y;
    glfwGetCursorPos(_window, &x, &y);

    _camera->OnMouseMove(x, y, glfwGetMouseButton(_window, 0) == GLFW_PRESS);
}

// Callbacks
void OpenGLContext::OnWindowResize(GLFWwindow *window, int width, int height)
{
    auto glContext = static_cast<OpenGLContext *>(glfwGetWindowUserPointer(window));
    glContext->Width = width;
    glContext->Height = height;
}

void OpenGLContext::OnScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    auto glContext = static_cast<OpenGLContext *>(glfwGetWindowUserPointer(window));
    glContext->GetCamera()->OnScroll(yoffset);
}
