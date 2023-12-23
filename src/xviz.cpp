/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 21:02:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 15:41:57
 */
#include <iostream>
#include "xviz.h"

namespace xviz
{

    float Xviz::s_displayScale = 1.0f;
    Settings Xviz::s_settings;
    b2Vec2 Xviz::s_clickPointWS = b2Vec2_zero;
    bool Xviz::s_rightMouseDown = false;
    Sence Xviz::s_sence;
    GLFWwindow *g_mainWindow;

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
        // 加载配置文件
        s_settings.Load();
        // 相机的长宽
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
        g_mainWindow = glfwCreateWindow(g_camera.m_width, g_camera.m_height, "Xviz", NULL, NULL);

        if (g_mainWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwGetWindowContentScale(g_mainWindow, &s_displayScale, &s_displayScale);
        glfwMakeContextCurrent(g_mainWindow);
        int version = gladLoadGL(glfwGetProcAddress);
        //    设置各种信号
        SetCallback();
        g_debugDraw.Create();
        CreateUI(g_mainWindow, glsl_version);

        fileDialog.SetTitle("title");
        fileDialog.SetTypeFilters({".h", ".cpp"});

        return true;
    }

    void Xviz::Run()
    {
        std::cout << "run " << std::endl;
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        std::chrono::duration<double> frameTime(0.0);
        std::chrono::duration<double> sleepAdjust(0.0);

        while (!glfwWindowShouldClose(g_mainWindow))
        {

            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

            glfwGetWindowSize(g_mainWindow, &g_camera.m_width, &g_camera.m_height);
            int bufferWidth, bufferHeight;
            glfwGetFramebufferSize(g_mainWindow, &bufferWidth, &bufferHeight);
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

            glfwSwapBuffers(g_mainWindow);
            glfwPollEvents();

            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            std::chrono::duration<double> target(1.0 / s_settings.m_hertz);
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
        s_sence.Draw(s_settings);
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
        const char *fontPath = "../data/msyh.ttf";
        io.Fonts->AddFontFromFileTTF(fontPath, 8.0f * s_displayScale,
                                     nullptr, io.Fonts->GetGlyphRangesChineseFull());
    }

    void Xviz::SetCallback()
    {
        glfwSetWindowSizeCallback(g_mainWindow, ResizeWindowCallback);
        glfwSetKeyCallback(g_mainWindow, KeyCallback);
        glfwSetCharCallback(g_mainWindow, CharCallback);
        glfwSetMouseButtonCallback(g_mainWindow, MouseButtonCallback);
        glfwSetCursorPosCallback(g_mainWindow, MouseMotionCallback);
        glfwSetScrollCallback(g_mainWindow, ScrollCallback);
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
        double xd, yd;
        glfwGetCursorPos(g_mainWindow, &xd, &yd);
        b2Vec2 ps((float)xd, (float)yd);
        // Use the mouse to move things around.
        if (button == GLFW_MOUSE_BUTTON_1)
        {
            //<##>
            // ps.Set(0, 0);
            b2Vec2 pw = g_camera.ConvertScreenToWorld(ps);
            if (action == GLFW_PRESS)
            {
                if (mods == GLFW_MOD_SHIFT)
                {
                    s_sence.ShiftMouseDown(pw);
                }
                else
                {
                    s_sence.MouseDown(pw);
                }
            }

            if (action == GLFW_RELEASE)
            {
                s_sence.MouseUp(pw);
            }
        }
        else if (button == GLFW_MOUSE_BUTTON_2)
        {
            if (action == GLFW_PRESS)
            {
                s_clickPointWS = g_camera.ConvertScreenToWorld(ps);
                s_rightMouseDown = true;
            }

            if (action == GLFW_RELEASE)
            {
                s_rightMouseDown = false;
            }
        }
    }
    void Xviz::MouseMotionCallback(GLFWwindow *, double xd, double yd)
    {
        b2Vec2 ps((float)xd, (float)yd);

        b2Vec2 pw = g_camera.ConvertScreenToWorld(ps);
        
        s_sence.MouseMove(pw);

        if (s_rightMouseDown)
        {
            b2Vec2 diff = pw - s_clickPointWS;
            g_camera.m_center.x -= diff.x;
            g_camera.m_center.y -= diff.y;
            s_clickPointWS = g_camera.ConvertScreenToWorld(ps);
        }
    }
    void Xviz::ScrollCallback(GLFWwindow *window, double dx, double dy)
    {
        // std::cout << "dx is " << dx << " dy is " << dy << std::endl;

        // ImGui_ImplGlfw_ScrollCallback(window, dx, dy);
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

        // 更新菜单栏
        UpdateMenuBar();
        // 更新参数
        UpdateSettings();

        /**
                ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

                if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                {
                    fileDialog.Open();
                }
                ImGui::SliderFloat("Hertz", &s_settings.m_hertz, 5.0f, 120.0f, "%.0f hz");

                ImGui::End();
                fileDialog.Display();

                if (fileDialog.HasSelected())
                {
                    std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
                    fileDialog.ClearSelected();
                }
                **/
    }

    void Xviz::UpdateMenuBar()
    {

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("文件"))
            {
                if (ImGui::MenuItem("ddd"))
                {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("编辑"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z"))
                {
                }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
                {
                } // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X"))
                {
                }
                if (ImGui::MenuItem("Copy", "CTRL+C"))
                {
                }
                if (ImGui::MenuItem("Paste", "CTRL+V"))
                {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void Xviz::UpdateSettings()
    {
        float menuWidth = 180.0f * s_displayScale;
        if (g_debugDraw.m_showUI)
        {
            ImGui::SetNextWindowPos({g_camera.m_width - menuWidth - 10.0f, 20.0f});
            ImGui::SetNextWindowSize({menuWidth, g_camera.m_height - 20.0f});
            ImGui::Begin("Tools");
            if (ImGui::BeginTabBar("ControlTabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Settings"))
                {
                    ImGui::SliderFloat("Hertz", &s_settings.m_hertz, 5.0f, 120.0f, "%.0f hz");
                    ImGui::Checkbox("绘制网络", &s_settings.m_drawGrid);
                    ImGui::SliderInt("网格宽度", &s_settings.m_gridWidth, 1, 40);
                    ImGui::SliderInt("网格高度", &s_settings.m_gridHeight, 1, 40);
                    ImGui::Checkbox("绘制原点", &s_settings.m_drawOrigin);
                    ImGui::Checkbox("绘制鼠标", &s_settings.m_drawMousePose);
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
        }
    }
} // namespace xviz
