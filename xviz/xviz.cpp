/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 21:02:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-25 23:15:01
 */
#include <iostream>
#include "xviz.h"
#include "colors.h"
#include "image.h"
namespace xviz
{

    float Xviz::s_displayScale = 1.0f;
    Settings Xviz::s_settings;
    b2Vec2 Xviz::s_clickPointWS = b2Vec2_zero;
    bool Xviz::s_rightMouseDown = false;
    GLFWwindow *g_mainWindow;

    Xviz::Xviz()
    {
    }
    Xviz::~Xviz()
    {
        g_debugDraw.Destroy();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
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
        m_communication.Init(s_settings.m_subConnect);

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

        m_fileDialog.SetTitle("文件加载");
        m_fileDialog.SetTypeFilters({".png", ".json"});

        return true;
    }

    void Xviz::Run()
    {
        std::cout << "run " << std::endl;
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        std::chrono::duration<double> frameTime(0.0);
        std::chrono::duration<double> sleepAdjust(0.0);
        m_communication.Run();

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
            // std::cout << "new frame " << std::endl;

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
            glfwSwapBuffers(g_mainWindow); // 双缓冲
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
        // std::cout << "draw " << std::endl;
        g_sence.Draw(s_settings);

        // ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
    }

    void Xviz::CreateUI(GLFWwindow *window, const char *glslVersion)
    {

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
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glslVersion);
        // 设置微软雅黑中文字体
        const char *fontPath = "../data/msyh.ttf";
        io.Fonts->AddFontFromFileTTF(fontPath, s_settings.m_fontSize * s_displayScale,
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
                    g_sence.ShiftMouseDown(pw);
                }
                else
                {
                    g_sence.MouseDown(pw);
                }
            }

            if (action == GLFW_RELEASE)
            {
                g_sence.MouseUp(pw);
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

        g_sence.MouseMove(pw);

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
    }

    void Xviz::UpdateMenuBar()
    {

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("文件"))
            {
                if (ImGui::MenuItem("添加图片"))
                {
                    m_fileDialog.Open();
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

        m_fileDialog.Display();

        if (m_fileDialog.HasSelected())
        {

            std::string pngFile = m_fileDialog.GetSelected().string();

            m_fileDialog.ClearSelected();
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
                    ImGui::SliderInt("字体大小", &s_settings.m_fontSize, 10, 20);
                    ImGui::SliderFloat("画面频率", &s_settings.m_hertz, 5.0f, 120.0f, "%.0f hz");
                    ImGui::Checkbox("绘制网络", &s_settings.m_drawGrid);
                    ImGui::SliderInt("网格宽度", &s_settings.m_gridWidth, 1, 40);
                    ImGui::SliderInt("网格高度", &s_settings.m_gridHeight, 1, 40);
                    ImGui::Checkbox("绘制原点", &s_settings.m_drawOrigin);
                    ImGui::Checkbox("绘制鼠标", &s_settings.m_drawMousePose);
                    if (ImGui::TreeNode("绘制路径"))
                    {
                        for (auto &drawPath : g_sence.m_paths)
                        {
                            const std::string path_name = drawPath.first;

                            ImGui::Checkbox(path_name.data(), &g_sence.m_paths[path_name].draw);

                            ImGui::Combo((path_name + ":color").data(), &g_sence.m_paths[path_name].color, m_colorItems, IM_ARRAYSIZE(m_colorItems));
                            ImGui::SliderFloat((path_name + ":width").data(), &g_sence.m_paths[path_name].width, 0.01, 0.5);
                        }
                        ImGui::TreePop();
                    }

                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::End();
        }
    }
} // namespace xviz
