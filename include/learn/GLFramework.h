#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "learn/shader_s.h"

struct GLRenderData {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int shaderProgramID;
    std::shared_ptr<Shader> shader;
};

class GLFramework {
public:
    static void Init(int width, int height, const char* title);
    static void RunRenderLoop();
    static void SetRenderAndRelease(std::function<void()> renderFunc, std::function<void()> releaseFunc);
    static void Terminate();
    
    static GLFWwindow* GetWindow();
    
private:
    static GLFWwindow* window;
    static void processInput(GLFWwindow* window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};