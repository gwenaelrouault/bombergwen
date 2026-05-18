#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <syslog.h>
#include <string>
#include <memory>
#include <stdexcept>
#include "game_engine.h"

using namespace std;

void game_loop(shared_ptr<GameEngine> engine, SDL_Renderer *renderer)
{
    bool running = true;
    SDL_Event event;
    syslog(LOG_INFO, "main loop - START");

    Uint32 delta_time = 0;
    constexpr Uint32 TIME_FRAME = 20;
    
    cout << " === MAIN LOOP ===" << endl;
    while (running)
    {
        Uint32 start_time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("QUIT EVENT\n");
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    printf("ESC -> quit\n");
                    running = false;
                }
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    engine->on_DOWN();
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    engine->on_RIGHT();
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    engine->on_LEFT();
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    engine->on_UP();
                }
            }
        }
        engine->update(TIME_FRAME);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        engine->draw(renderer);
        SDL_RenderPresent(renderer);
        Uint32 end_time = SDL_GetTicks();
        delta_time = end_time - start_time;
        //cout << "DELTA " << delta_time << "(" << start_time << "," << end_time << ")" << endl;
        Uint32 time_to_delay = TIME_FRAME - delta_time;
        if (time_to_delay > 0) {
            SDL_Delay(time_to_delay);
        }
    }
    syslog(LOG_INFO, "main loop - END");
}

int main(int argc, char **argv)
{
    openlog("bombergwen", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "init SDL");
    SDL_Window *window = NULL;

    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        syslog(LOG_ERR, "%s", SDL_GetError());
        return EXIT_FAILURE;
    }
    syslog(LOG_INFO, "init windows");
    window = SDL_CreateWindow(
        "Bombergwen",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        320, 240,
        SDL_WINDOW_HIDDEN);
    bool fullscreen = true;
    if (argc > 1)
    {
        std::string opt = argv[1];
        if (opt == "-desktop")
        {
            fullscreen = false;
        }
    }
    if (!window)
    {
        syslog(LOG_ERR, "%s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Delay(100);
    syslog(LOG_INFO, "init renderer");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        syslog(LOG_ERR, "%s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_ShowWindow(window);
    if (fullscreen)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    shared_ptr<GameEngine> engine = std::make_shared<GameEngine>();
    engine->load();
    engine->init(renderer);

    game_loop(engine, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}