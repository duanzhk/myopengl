#include <learn/shader_s.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <functional>
#include "learn/GLFramework.h"

void render5()
{
    // build and compile our shader program
    auto myShader = std::make_shared<Shader>("shaders/3.3.shader.vs", "shaders/3.3.shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    auto rdata = std::make_shared<GLRenderData>();
    rdata->shaderProgramID = myShader->shaderProgramID;
    rdata->VAO = VAO;
    rdata->VBO = VBO;
    rdata->shader = myShader;

    std::cout << "Shader Program ID: " << myShader->shaderProgramID << std::endl;
    GLint isLinked = 0;
    glGetProgramiv(myShader->shaderProgramID, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        std::cerr << "Shader program not properly linked!" << std::endl;
        GLint maxLength = 0;
        glGetProgramiv(myShader->shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(myShader->shaderProgramID, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Linker error: " << infoLog.data() << std::endl;
        return;
    }

    // render loop
    auto render = [rdata]()
    {
        rdata->shader->use();
        glBindVertexArray(rdata->VAO);

        // GLint program;
        // glGetIntegerv(GL_CURRENT_PROGRAM, &program);
        // std::cout << "Current program: " << program << std::endl;

        // GLint vao;
        // glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
        // std::cout << "Bound VAO: " << vao << std::endl;

        glDrawArrays(GL_TRIANGLES, 0, 3);
    };

    // optional: de-allocate all resources once they've outlived their purpose:
    auto release = [rdata]()
    {
        glDeleteVertexArrays(1, &rdata->VAO);
        glDeleteBuffers(1, &rdata->VBO);
    };
    GLFramework::SetRenderAndRelease(render, release);
}