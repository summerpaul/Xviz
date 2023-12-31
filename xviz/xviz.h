/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 21:02:17
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 21:42:37
 */
#include <stdint.h>

#ifndef __XVIZ_H__
#define __XVIZ_H__
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <thread>
#include <chrono>
#include <memory>

#include "draw.h"
#include "settings.h"
#include "sence.h"
#include "imfilebrowser.h"
#include "communication.h"
#include "images.h"
namespace xviz
{

    class Xviz
    {
    public:
        typedef std::unique_ptr<Xviz> Ptr;

    public:
        Xviz();
        ~Xviz();
        bool Init();
        void Run();

    private:
        void Draw();
        void SetCallback();
        void UpdateUI();
        void UpdateMenuBar();
        void UpdateSettings();

    private:
        static void CreateUI(GLFWwindow *window, const char *glslVersion = NULL);

        static void ResizeWindowCallback(GLFWwindow *, int width, int height);
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void CharCallback(GLFWwindow *window, unsigned int c);
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void MouseMotionCallback(GLFWwindow *, double xd, double yd);
        static void ScrollCallback(GLFWwindow *window, double dx, double dy);

    private:
        static float s_displayScale;
        static Settings s_settings;

        static b2Vec2 s_clickPointWS;
        static bool s_rightMouseDown;

        ImGui::FileBrowser m_fileDialog;
        Communication m_communication;

        const char *m_colorItems[5] = {"WHITE",
                                      "BLACK",
                                      "RED",
                                      "GREEN",
                                      "BLUE"};
    };

} // namespace xviz

#endif /* __XVIZ_H__ */
