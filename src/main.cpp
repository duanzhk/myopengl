#include <iostream>
#include <vector>
#include <functional>
#include "learn/GLFramework.h"

void render1();
void render2();
void render3();
void render4();
void render5();
void render6();
void render7();

// 渲染函数映射表
static const std::vector<std::function<void()>> rendersFuncs = {
    []() { /* 空函数，索引0不使用 */ },
    render1, render2, render3, render4,
    render5, render6, render7
};

int main(int argc, char const *argv[])
{
    try
    {
        
        // 根据参数选择要运行的示例
        if (argc > 1)
        {
            int lesson = std::stoi(argv[1]);
            // 初始化框架
            GLFramework::Init(800, 600, ("MyLearnOpenGL(" + std::to_string(lesson) + ")").c_str());
            if (lesson > 0 && lesson < rendersFuncs.size())
            {
                rendersFuncs[lesson](); // 调用对应的渲染函数
            }
            else
            {
                std::cout << "Invalid lesson number (1-" << rendersFuncs.size() - 1 << ")" << std::endl;
            }
        }
        else
        {
            std::cout << "Usage: " << argv[0] << " <lesson_number>" << std::endl;
            return -1;
        }

        // 运行渲染循环
        GLFramework::RunRenderLoop();
        
        // 退出并清理资源
        std::cout << "Render loop ended." << std::endl;
        GLFramework::Terminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}