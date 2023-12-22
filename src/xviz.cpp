/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 21:02:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 00:19:20
 */
#include <iostream>
#include "xviz.h"

namespace xviz
{

    float Xviz::s_displayScale = 1.0f;
    Settings Xviz::s_settings;
    b2Vec2 Xviz::s_clickPointWS = b2Vec2_zero;

    Xviz::Xviz()
    {
    }
    Xviz::~Xviz()
    {
        g_debugDraw.Destroy();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        glfwTerminate();

        s_settings.Save();
    }
    bool Xviz::Init()
    {
        s_settings.Load();

        g_camera.m_width = s_settings.m_windowWidth;
        g_camera.m_height = s_settings.m_windowHeight;

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
        m_window = glfwCreateWindow(g_camera.m_width, g_camera.m_height, "Xviz", NULL, NULL);

        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwGetWindowContentScale(m_window, &s_displayScale, &s_displayScale);
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
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        std::chrono::duration<double> frameTime(0.0);
        std::chrono::duration<double> sleepAdjust(0.0);

        while (!glfwWindowShouldClose(m_window))
        {

            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

            glfwGetWindowSize(m_window, &g_camera.m_width, &g_camera.m_height);
            int bufferWidth, bufferHeight;
            glfwGetFramebufferSize(m_window, &bufferWidth, &bufferHeight);
            glViewport(0, 0, bufferWidth, bufferHeight);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 开始新的一帧
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (g_debugDraw.m_showUI)
            {
                ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
                ImGui::SetNextWindowSize(ImVec2(float(g_camera.m_width), float(g_camera.m_height)));
                ImGui::SetNextWindowBgAlpha(0.0f);
                ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
                ImGui::End();
            }

            Draw();
            UpdateUI();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_window);
            glfwPollEvents();

            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            std::chrono::duration<double> target(1.0 / 60.0);
            std::chrono::duration<double> timeUsed = t2 - t1;
            std::chrono::duration<double> sleepTime = target - timeUsed + sleepAdjust;
            if (sleepTime > std::chrono::duration<double>(0))
            {
                std::this_thread::sleep_for(sleepTime);
            }
        }
    }

    void Xviz::Draw()
    {

        g_debugDraw.DrawString(b2Vec2(100,100),"kkk");
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
        g_camera.m_width = width;
        g_camera.m_height = height;
        s_settings.m_windowWidth = width;
        s_settings.m_windowHeight = height;
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

        ImGui_ImplGlfw_ScrollCallback(window, dx, dy);
        if (ImGui::GetIO().WantCaptureMouse)
        {
            return;
        }

        if (dy > 0)
        {
            g_camera.m_zoom /= 1.1f;
        }
        else
        {
            g_camera.m_zoom *= 1.1f;
        }
    }

    void Xviz::UpdateUI()
    {

        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

        if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        {
        }
        ImGui::SliderFloat("Hertz", &s_settings.m_hertz, 5.0f, 120.0f, "%.0f hz");

        ImGui::End();
    }
} // namespace xviz
