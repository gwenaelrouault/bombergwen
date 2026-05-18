#pragma once

#include <string>
#include <SDL2/SDL_image.h>
#include <memory>

using namespace std;

class SpriteSheet {
public:
    SpriteSheet(const string& filename) : _sp_filename(filename) {
        _sp_surface = IMG_Load(filename.c_str());
    }
    virtual ~SpriteSheet() {
        SDL_FreeSurface( _sp_surface );
    }

    shared_ptr<SDL_Surface> load(int x, int y, int width, int height);
private:
    string _sp_filename;
    SDL_Surface* _sp_surface;
};