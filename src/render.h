#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "main.h"


namespace render
{
    EFuncState init ();
    void tick ();
    void close ();
}
