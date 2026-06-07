#include "bomber_input.h"
#include <SDL2/SDL.h>

vector<T_BomberKeyEvent> BomberInputManager::process_events()
{
    vector<T_BomberKeyEvent> events;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            events.push_back(BOMBER_QUIT);
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                events.push_back(BOMBER_KEY_ESCAPE);
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                events.push_back(BOMBER_KEY_DOWN);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                events.push_back(BOMBER_KEY_RIGHT);
            }
            else if (event.key.keysym.sym == SDLK_LEFT)
            {
                events.push_back(BOMBER_KEY_LEFT);
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                events.push_back(BOMBER_KEY_UP);
            }
            else if (event.key.keysym.sym == SDLK_SPACE)
            {
                events.push_back(BOMBER_KEY_ACTION);
            }
        } else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                events.push_back(BOMBER_KEY_DOWN_CANCEL);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                events.push_back(BOMBER_KEY_RIGHT_CANCEL);
            }
            else if (event.key.keysym.sym == SDLK_LEFT)
            {
                events.push_back(BOMBER_KEY_LEFT_CANCEL);
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                events.push_back(BOMBER_KEY_UP_CANCEL);
            }
        }
    }
    return events;
}