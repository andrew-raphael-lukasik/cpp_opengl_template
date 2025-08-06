#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

void framebuffer_size_changed_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    spdlog::error("window size changed to: {} : {}", width, height);
}

void error_callback(int error, const char* description)
{
    spdlog::error("Error: {}", description);
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// src: https://iquilezles.org/articles/palettes/
glm::vec3 palette( const float t, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d ) { return a + b*cos(6.283185f*(c*t+d)); }

int main ()
{
    auto file_logger = spdlog::basic_logger_mt("file_logger", "log.txt", true);
    spdlog::set_default_logger(file_logger);
    spdlog::info("program started");

    if (!glfwInit())
    {
        spdlog::error("glfwInit() failed");
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "hello opengl", NULL, NULL);
    if (!window) {
        spdlog::error("glfwCreateWindow() failed");
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_changed_callback);
    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();

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
