#pragma once

#include <GLFW/glfw3.h>

#include "main.h"


namespace app
{
    extern bool alive;
    extern GLFWwindow* window;

    EFuncState init ();
    void tick ();
    void close ();
}
