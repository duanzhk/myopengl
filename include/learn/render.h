#pragma once

struct RenderContext {
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
};

// 声明render函数
RenderContext render();  