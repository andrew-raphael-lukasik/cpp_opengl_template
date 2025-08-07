#pragma once

#include "main_shared.cpp"

#include <GLFW/glfw3.h>


namespace game
{
    EFuncState init ()
    {
        return EFuncState::Succeded;
    }

    void tick ()
    {
        double time = glfwGetTime();
    }

    void close ()
    {
        
    }
}
