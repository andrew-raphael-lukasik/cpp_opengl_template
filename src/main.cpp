#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main ()
{
    auto file_logger = spdlog::basic_logger_mt("file_logger", "log.txt");
    spdlog::set_default_logger(file_logger);
    spdlog::info("program started");

    if (!glfwInit())
    {
        spdlog::error("glfwInit() failed");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "hello opengl", NULL, NULL);
    if (!window) {
        spdlog::error("glfwCreateWindow() failed");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    spdlog::info("program was closed");
    glfwTerminate();
}
