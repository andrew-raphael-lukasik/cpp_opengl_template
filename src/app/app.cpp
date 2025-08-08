#include "app.h"
#include "../main.h"

#include <filesystem>
#include <bits/unique_ptr.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <GLFW/glfw3.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace app
{
    
    bool alive;
    GLFWwindow* window;


    void error_callback(int error, const char* description)
    {
        spdlog::error("Error: {}", description);
        fprintf(stderr, "Error: %s\n", description);
    }


    EFuncState init ()
    {
        // create file logger
        auto file_logger = spdlog::basic_logger_mt("file_logger", "log.txt", true);
        spdlog::set_default_logger(file_logger);
        spdlog::info("program started");
        spdlog::info("current working directory: {}", std::filesystem::current_path().string());

        // initialize glfw
        if (!glfwInit())
        {
            spdlog::error("glfwInit() failed");
            return EFuncState::Failed;
        }
        glfwSetErrorCallback(error_callback);

        // create window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(800, 600, "hello opengl", NULL, NULL);
        if (!window) {
            spdlog::error("glfwCreateWindow() failed");
            glfwTerminate();
            return EFuncState::Failed;
        }
        glfwMakeContextCurrent(window);

        alive = true;
        return EFuncState::Succeded;
    }

    void tick ()
    {
        if (glfwWindowShouldClose(app::window)) {
            alive = false;
        }
    }

    void close ()
    {
        alive = false;
        glfwDestroyWindow(window);
        glfwTerminate();
        spdlog::info("program has ended");
    }

}
