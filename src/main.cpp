#include <spdlog/spdlog.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "main.h"
#include "render/render.h"
#include "input/input.h"
#include "app/app.h"
#include "game/game.h"


int main ()
{
    // initialize every module
    if (app::init()!=EFuncState::Succeded) {
        spdlog::error("app::init() failed, closing program now");
        return -1;
    }
    if (game::init()!=EFuncState::Succeded) {
        spdlog::error("game::init() failed, closing program now");
        return -1;
    }
    if (input::init()!=EFuncState::Succeded) {
        spdlog::error("input::init() failed, closing program now");
        return -1;
    }
    if (render::init()!=EFuncState::Succeded) {
        spdlog::error("render::init() failed, closing program now");
        return -1;
    }

    // main program loop
    while (app::alive)
    {
        // tick every module
        app::tick();
        input::tick();
        game::tick();
        render::tick();
        
        glfwPollEvents();
    }

    // close every module
    game::close();
    input::close();
    render::close();
    app::close();

    return 0;
}
