#include <GLFW/glfw3.h>

#include "main.h"
#include "game.h"


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
