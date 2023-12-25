/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-25 23:57:26
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-26 00:40:55
 */


#include "program.h"
int main(int argc, char const *argv[])
{
    if (glfwInit() == GLFW_FALSE)
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "XVIZ", NULL, NULL);
    if (window == 0)
    {
        glfwTerminate();
        return -1;
    }
    using namespace xviz;
    auto app = xviz::Program::GetInstance();
    app->Init(window);

    glfwSetKeyCallback(window, Program::KeyActionCallback);
    glfwSetCursorPosCallback(window, Program::CursorPosCallback);
    glfwSetScrollCallback(window, Program::ScrollCallback);
    glfwSetMouseButtonCallback(window, Program::MouseButtonCallback);

    glfwSetWindowSizeCallback(window, Program::ResizeCallback);
    glfwMakeContextCurrent(window);

    // glfwGetWindowContentScale(window, &s_displayScale, &s_displayScale);
    
    
    if (app->SetUp())
    {
        while (glfwWindowShouldClose(window) == 0)
        {
            // 开始新的一帧
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glfwWaitEvents();

            glClear(GL_COLOR_BUFFER_BIT);

            app->Render();

            glfwSwapBuffers(window);
        }
        app->CleanUp();
    }

    glfwTerminate();

    return 0;
}
