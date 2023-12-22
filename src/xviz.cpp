/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 21:02:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-22 23:08:24
 */
#include <iostream>
#include "xviz.h"

namespace xviz
{

    float Xviz::s_displayScale = 1.0f;

    Xviz::Xviz()
    {
    }
    Xviz::~Xviz()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    bool Xviz::Init()
    {
        if (glfwInit() == 0)
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            return false;
        }
        // 设置主要和次要版本
        const char *glsl_version = "#version 330";
        // 片段着色器将作用域每一个采样点（采用4倍抗锯齿，则每个像素有4个片段（四个采样点））

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);

        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(m_window);
        int version = gladLoadGL(glfwGetProcAddress);

        SetCallback();
        g_debugDraw.Create();
        CreateUI(m_window, glsl_version);

        return true;
    }
    void Xviz::Run()
    {
        std::cout << "run " << std::endl;
        //  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        while (!glfwWindowShouldClose(m_window))
        {

            // 开始新的一帧
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Draw();
            UpdateUI();
            glfwPollEvents();



            // 渲染GUI
            ImGui::Render();

            int display_w, display_h;
            glfwGetFramebufferSize(m_window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Xviz::Draw()
    {
        // std::cout << "draw " << std::endl;
    }

    void Xviz::CreateUI(GLFWwindow *window, const char *glslVersion)
    {

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        // Setup Dear ImGui style
        // ImGui::StyleColorsDark();
        ImGui::StyleColorsLight();

        ImGui_ImplGlfw_InitForOpenGL(window, true);

        ImGui_ImplOpenGL3_Init(glslVersion);
    }

    void Xviz::SetCallback()
    {
        glfwSetWindowSizeCallback(m_window, ResizeWindowCallback);
        glfwSetKeyCallback(m_window, KeyCallback);
        glfwSetCharCallback(m_window, CharCallback);
        glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
        glfwSetCursorPosCallback(m_window, MouseMotionCallback);
        glfwSetScrollCallback(m_window, ScrollCallback);
    }

    void Xviz::ResizeWindowCallback(GLFWwindow *, int width, int height)
    {
        std::cout << "ResizeWindowCallback" << std::endl;
    }
    void Xviz::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
    }
    void Xviz::CharCallback(GLFWwindow *window, unsigned int c)
    {
    }
    void Xviz::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
    }
    void Xviz::MouseMotionCallback(GLFWwindow *, double xd, double yd)
    {
    }
    void Xviz::ScrollCallback(GLFWwindow *window, double dx, double dy)
    {
    }

    void Xviz::UpdateUI()
    {

        float menuWidth = 180.0f * s_displayScale;

        if (g_debugDraw.m_showUI)
        {
            ImGui::SetNextWindowPos({g_camera.m_width - menuWidth - 10.0f, 10.0f});
            ImGui::SetNextWindowSize({menuWidth, g_camera.m_height - 20.0f});

            ImGui::Begin("Tools", &g_debugDraw.m_showUI, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            ImGui::End();
        }
    }
} // namespace xviz
