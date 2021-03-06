#include "agpch.h"

#include "Events/ApplicationEvents.h"
#include "Events/MouseEvent.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Agate
{


    Window::Window(std::string WindowName, int size_x, int size_y, EventCallbackFn callback, bool vsync)
        : m_windowProps{WindowName, size_x, size_y, callback, vsync}
    {
        InitWindow();
    }

    void Window::InitWindow()
    {
        if (!glfwInit())
            PRINTCRIT("GLFW FAILED INIT-------------------");
        glfwSetErrorCallback(GlfwError);

        m_Window = glfwCreateWindow(m_windowProps.width, m_windowProps.height, m_windowProps.name.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            PRINTCRIT("GLAD failed to init");
            throw -1;
        }

        glfwSetWindowUserPointer(m_Window, &m_windowProps);


        //SetVSync(true);//need glad to define this function or maybe not--------------------------------------------------------------------------------------------------------

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            //need this bc lambda can't access non-static class members
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.callback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xpos, double ypos) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            MouseMoved event((int) xpos, (int) ypos);
            data.callback(event);
        });
    }

    void Window::GlfwError(int error_code, const char *description)
    {
        PRINTCRIT("GLFW ERROR---CODE:" + std::to_string(error_code) + " :" + description);
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::GetWidth()
    {
    }

    void Window::GetHieght()
    {
    }

    void Window::SetVSync(bool enable)
    {
        if (enable)
        {
            glfwSwapInterval(1);
            m_windowProps.VSyncState = true;
        }
        else
        {
            glfwSwapInterval(0);
            m_windowProps.VSyncState = false;
        }
    }

    bool Window::GetVSyncState()
    {
        return m_windowProps.VSyncState;
    }
    GLFWwindow *Window::GetWindow()
    {
        return m_Window;
    }


}// namespace Agate
