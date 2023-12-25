/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-25 23:26:04
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-26 00:40:14
 */
#include <iostream>

using namespace std;

#include "program.h"
namespace xviz
{

    Program *Program::GetInstance()
    {
        static Program app;
        return &app;
    }

    bool Program::Init(GLFWwindow *window)
    {
        if (window == nullptr)
        {
            return false;
        }

        if (m_window != nullptr)
        {
            return false;
        }
        m_window = window;
        glfwSetWindowUserPointer(m_window, static_cast<void *>(this));
        return true;
    }

    Program::~Program()
    {
        glfwSetWindowUserPointer(m_window, nullptr);
    }

    bool Program::SetUp()
    {

        glfwMakeContextCurrent(m_window);
        gladLoadGL(glfwGetProcAddress);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext(); // 创建上下文
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 允许键盘控制
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // 允许游戏手柄控制

        // Setup Dear ImGui style
        // ImGui::StyleColorsDark();
        ImGui::StyleColorsLight();
        // 设置渲染器后端
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        const char *glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);
        // 设置微软雅黑中文字体

        return true;
    }
    void Program::Render()
    {
    }
    void Program::CleanUp()
    {
    }

    void Program::KeyActionCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
    }
    void Program::ResizeCallback(GLFWwindow *window, int width, int height)
    {
    }
    void Program::CursorPosCallback(GLFWwindow *window, double x, double y)
    {
    }
    void Program::ScrollCallback(GLFWwindow *window, double x, double y)
    {
    }
    void Program::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
    }

} // namespace xviz
