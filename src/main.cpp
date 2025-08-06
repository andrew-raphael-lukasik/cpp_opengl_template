#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

// src: https://iquilezles.org/articles/palettes/
glm::vec3 palette( const float t, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d ) { return a + b*cos(6.283185f*(c*t+d)); }

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
        float time = glfwGetTime();

        glm::vec3 bg(palette(time*.1f,glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(2.0,1.0,0.0),glm::vec3(0.5,0.20,0.25)));
        glClearColor(bg.r, bg.g , bg.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    spdlog::info("program was closed");
    glfwTerminate();
    return 0;
}
