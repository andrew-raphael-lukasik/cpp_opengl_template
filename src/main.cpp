#include <bits/unique_ptr.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_PERLIN_IMPLEMENTATION
#include "stb/stb_perlin.h"

#include "main_shared.cpp"
#include "rendering.cpp"



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

int main ()
{
    // create file logger
    auto file_logger = spdlog::basic_logger_mt("file_logger", "log.txt", true);
    spdlog::set_default_logger(file_logger);
    spdlog::info("program started");

    // initialize glfw
    if (!glfwInit())
    {
        spdlog::error("glfwInit() failed");
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    // create window
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

    // create renderer
    auto renderer = std::make_unique<Renderer>();
    if (renderer.get()->init(window)!=EFuncState::Succeded)
    {
        return -1;
    }

    // main program loop
    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();
        
        renderer.get()->tick(window);
        
        glfwPollEvents();
    }

    // shut down gracefully
    spdlog::info("program was closed");
    glfwTerminate();
    return 0;
}
