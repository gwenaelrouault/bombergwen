#include "spritesheet.h"
#include "bomber_logger.h"

shared_ptr<SDL_Surface> SpriteSheet::load(int x, int y, int width, int height) {
    BomberLogger::get_instance()->debug("GAME:ENGINE:ASSETS:ASSET:spritesheet:load({},{},{},{}) - START", x, y, width, height);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_Rect dst_rect;
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.w = width;
    dst_rect.h = height;
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_BlitSurface(_sp_surface, &rect, surface, &dst_rect);
    BomberLogger::get_instance()->debug("GAME:ENGINE:ASSETS:ASSET:spritesheet:load({},{},{},{}) - END", x, y, width, height);
    return shared_ptr<SDL_Surface> (surface, SDL_FreeSurface);
}
