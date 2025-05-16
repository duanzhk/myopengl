#include "learn/GLFramework.h"

GLFWwindow *GLFramework::window = nullptr;
std::function<void()> releaseFunc = nullptr;
std::function<void()> renderFunc = nullptr;

void GLFramework::Init(int width, int height, const char *title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        GLFramework::Terminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void GLFramework::RunRenderLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (renderFunc)
        {
            renderFunc();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow *GLFramework::GetWindow()
{
    return GLFramework::window;
}

void GLFramework::SetRenderAndRelease(std::function<void()> render, std::function<void()> release)
{
    renderFunc = render;
    releaseFunc = release;
}

void GLFramework::Terminate()
{
    if (releaseFunc)
    {
        releaseFunc();
    }
    glfwTerminate();
}

void GLFramework::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void GLFramework::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}