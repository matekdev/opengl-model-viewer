#include "opengl_context.hpp"

int main()
{
    auto window = OpenGLContext(1024, 720, "OpenGL Model Viewer");
    window.Run();
}
