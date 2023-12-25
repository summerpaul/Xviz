/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-25 23:25:59
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-26 00:40:54
 */

#ifndef __PROGRAM_H__
#define __PROGRAM_H__
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace xviz
{

    class Program
    {
    public:
        static Program *GetInstance();

        bool Init(GLFWwindow *window);
        bool SetUp();
        void Render();
        void CleanUp();

    public:
        static void KeyActionCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ResizeCallback(GLFWwindow *window, int width, int height);
        static void CursorPosCallback(GLFWwindow *window, double x, double y);
        static void ScrollCallback(GLFWwindow *window, double x, double y);
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    protected:
        void onKeyAction(int key, int scancode, int action, int mods);
        void onResize(int width, int height);
        void onMouseMove(int x, int y);
        void onMouseButton(int button, int action, int mods);
        void onScroll(int x, int y);

    private:
        Program() = default;
        ~Program();
        Program(const Program &) = delete;
        Program &operator=(const Program &) = delete;

    private:
        GLFWwindow *m_window = nullptr;
    };

} // namespace xviz

#endif /* __PROGRAM_H__ */
