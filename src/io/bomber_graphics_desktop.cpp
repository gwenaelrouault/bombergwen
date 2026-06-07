#include "bomber_graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "bomber_logger.h"
#include <cmath>

unique_ptr<BomberGraphicsRenderer> BomberGraphicsRenderer::create_renderer(int screen_width, int screen_height)
{
    SDL_Window *window = NULL;
    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        BomberLogger::BomberLogger::get_instance()->error("%s", SDL_GetError());
        return nullptr;
    }
    window = SDL_CreateWindow(
        "Bombergwen",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width, screen_height,
        SDL_WINDOW_HIDDEN);
    if (window == nullptr)
    {
        BomberLogger::BomberLogger::get_instance()->error("%s", SDL_GetError());
        return nullptr;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetIntegerScale(renderer, SDL_FALSE);
    if (!renderer)
    {
        BomberLogger::BomberLogger::get_instance()->error("%s", SDL_GetError());
        SDL_DestroyWindow(window);
        return nullptr;
    }
    return make_unique<BomberGraphicsRenderer>(renderer, screen_width, screen_height, window);
}

void BomberGraphicsRenderer::draw(BomberTexture *texture, BomberCoordinates &coords)
{
    double screen_x1 = coords.get_x() - _screen_x_offset;
    double screen_y1 = coords.get_y() - _screen_y_offset;
    double screen_x2 = screen_x1 + texture->get_width();
    double screen_y2 = screen_y1 + texture->get_height();

    SDL_FRect box;
    box.x = screen_x1 * _x_scale_factor;
    box.y = screen_y1 * _y_scale_factor;
    box.w = texture->get_width() * _x_scale_factor;
    box.h = texture->get_height() * _y_scale_factor;
    SDL_RenderCopyF(_renderer, texture->get_texture(), NULL, &box);   
}