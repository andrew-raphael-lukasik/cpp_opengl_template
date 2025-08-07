#include "game.h"
#include "../main.h"

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
