#include "input.h"
#include "../main.h"
#include "../app/app.h"

#include <spdlog/spdlog.h>

#include <GLFW/glfw3.h>


namespace input
{

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        spdlog::info("input::key_callback( window:{} , key:{} , scancode:{} , action:{} , mods:{} )", (void*)window, key, scancode, action, mods);

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            spdlog::info("input::key_callback(): glfwSetWindowShouldClose()");
        }
    }


    EFuncState init ()
    {
        glfwSetKeyCallback(app::window, key_callback);
        return EFuncState::Succeded;
    }

    void tick ()
    {
        
    }

    void close ()
    {
        
    }
    
}
