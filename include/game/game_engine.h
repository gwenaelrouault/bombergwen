#pragma once

#include <SDL2/SDL.h>
#include "game_assets.h"
#include "sprites.h"
#include "game_entity.h"
#include "bomber_logger.h"
#include "world.h"
#include "bomber_input.h"

constexpr Uint32 TIME_FRAME_MS = 15;

class GameEngine
{
public:
    GameEngine(int screen_width, int screen_height): 
        _renderer(BomberGraphicsRenderer::create_renderer(screen_width, screen_height)),
        _assets(make_unique<GameAssets>()), 
        _world(make_unique<World>()), 
        _input_manager(make_unique<BomberInputManager>()) {}
    ~GameEngine() {}

    bool load();

    void init();

    bool update(int elapsed_ms);

    void draw();

    bool game_loop();

private:
    unique_ptr<BomberGraphicsRenderer> _renderer;
    unique_ptr<GameAssets> _assets;
    unique_ptr<World> _world;
    unique_ptr<BomberInputManager> _input_manager;

    bool game_cycle();
};