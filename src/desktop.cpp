#include <stdexcept>
#include <iostream>
#include <string>
#include <memory>
#include "game_engine.h"

int main(int argc, char **argv)
{
    bool result = EXIT_FAILURE;
    constexpr int SCREEN_WIDTH = 640;
    constexpr int SCREEN_HEIGHT = 480;
    BomberLogger logger;
    if (BomberLogger::get_instance() == nullptr) {
        return EXIT_FAILURE;
    }
    {
        auto game_engine = make_unique<GameEngine>(SCREEN_WIDTH, SCREEN_HEIGHT);
        result = game_engine->game_loop();
    }
    return result;
}