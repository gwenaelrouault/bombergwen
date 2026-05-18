#include "game_engine.h"

bool GameEngine::game_loop()
{
    BomberLogger::get_instance()->info("GAME:START");
    if (!load()) {
        return false;
    }
    init();
    bool running = true;
    while (running)
    {
        Uint32 start_cycle_time = SDL_GetTicks();
        running = game_cycle();
        Uint32 end_cycle_time = SDL_GetTicks();
        Uint32 cycle_time = end_cycle_time - start_cycle_time;
        if (cycle_time < TIME_FRAME_MS)
        {
            Uint32 cycle_time_delta = TIME_FRAME_MS - cycle_time;
            SDL_Delay(cycle_time_delta);
        }
    }
    BomberLogger::get_instance()->info("GAME:END");
    return true;
}

bool GameEngine::load()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:load - START");
    try
    {
        auto loaded_assets = _assets->load();
        auto sprites = ::get<0>(loaded_assets);
        auto levels = ::get<1>(loaded_assets);
        _world->load(sprites, levels);
        BomberLogger::get_instance()->info("GAME:ENGINE:load - END");
        return true;
    }
    catch (exception &e)
    {
        BomberLogger::get_instance()->error("GAME:ENGINE:load - ERROR({})", e.what());
    }
    return false;
}

void GameEngine::init()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:init - START");
    try {
        _renderer->show_window();
        _world->select_level("level1", _renderer.get());
        _world->init(_renderer.get());
    }
    catch (exception &e)
    {
        BomberLogger::get_instance()->error("GAME:ENGINE:init - ERROR({})", e.what());
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:init - END");
}

bool GameEngine::update(int elapsed_ms)
{
    vector<T_BomberKeyEvent> input_events = _input_manager->process_events();
    for(auto event : input_events)
    {
        if (event == BOMBER_QUIT || event == BOMBER_KEY_ESCAPE) {
            return false;
        }
        else if (event == BOMBER_KEY_UP)
        {
            _world->on_UP(_renderer.get());
        }
        else if (event == BOMBER_KEY_DOWN)
        {
            _world->on_DOWN(_renderer.get());
        }
        else if (event == BOMBER_KEY_LEFT)
        {
            _world->on_LEFT(_renderer.get());
        }
        else if (event == BOMBER_KEY_RIGHT)
        {
            _world->on_RIGHT(_renderer.get());
        }
        
    }
    _world->update(elapsed_ms);
    return true;
}

void GameEngine::draw()
{
    _world->draw(_renderer.get());
}

bool GameEngine::game_cycle()
{
    if (!update(TIME_FRAME_MS)) {
        return false;
    }
    _renderer->clear();
    draw();
    _renderer->display();
    return true;
}