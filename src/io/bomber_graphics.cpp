#include "bomber_graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "bomber_logger.h"
#include <cmath>

void BomberBBox::set_position(const BomberCoordinates &coords)
{
    _coords = coords;
    compute_rect();
}

void BomberBBox::set_dimension(double width, double height)
{
    _dimensions.set_width(width);
    _dimensions.set_height(height);
    compute_rect();
}

void BomberBBox::compute_rect()
{
    _rect.x1 = _coords.get_x() - _dimensions.get_width() / 2;
    _rect.y1 = _coords.get_y() - _dimensions.get_height() / 2;
    _rect.x2 = _coords.get_x() + _dimensions.get_width() / 2;
    _rect.y2 = _coords.get_y() + _dimensions.get_height() / 2;
}

BomberImg::BomberImg(SDL_Surface *surface)
{

    _surface = surface;
    if (surface != nullptr)
    {
        _width = surface->w;
        _height = surface->h;
        _bytes = surface->pitch * surface->h;
    }
    else
    {
        _width = 0;
        _height = 0;
        _bytes = 0;
    }
}

BomberImg::~BomberImg()
{
    if (_surface != nullptr)
    {
        SDL_FreeSurface(_surface);
    }
}

SDL_Surface *BomberImg::get_surface()
{
    return _surface;
}

BomberTexture::BomberTexture(SDL_Texture *texture, int width, int height)
{
    _texture = texture;
    _width = width;
    _height = height;
}

BomberTexture::~BomberTexture()
{
    SDL_DestroyTexture(_texture);
}

SDL_Texture *BomberTexture::get_texture()
{
    return _texture;
}


BomberGraphicsRenderer::BomberGraphicsRenderer(SDL_Renderer *renderer, int screen_width, int screen_height, SDL_Window *window)
{
    _renderer = renderer;
    _window = window;
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    _screen_width = screen_width;
    _screen_height = screen_height;
    _x_scale_factor = 1.0;
    _y_scale_factor = 1.0;
    _screen_x_offset = 0.0;
    _screen_y_offset = 0.0;
}

BomberGraphicsRenderer::~BomberGraphicsRenderer()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void BomberGraphicsRenderer::select_camera(BomberBBox *bbox)
{
    _bbox.set_position(bbox->get_coords());
    _bbox.set_dimension(bbox->get_dimensions().get_width(), bbox->get_dimensions().get_height());
    _x_scale_factor = (double)_screen_width / (double)bbox->get_dimensions().get_width();
    _y_scale_factor = (double)_screen_height / (double)bbox->get_dimensions().get_height();
    _screen_x_offset = _bbox.get_x() - _bbox.get_dimensions().get_width() / 2;
    _screen_y_offset = _bbox.get_y() - _bbox.get_dimensions().get_height() / 2;
    /*
    BomberLogger::get_instance()->info("IO:GRAPHICS:select_camera(x={},y={},w={},h={})",
                                       _bbox.get_x(), _bbox.get_y(), _bbox.get_dimensions().get_width(), _bbox.get_dimensions().get_height());
    BomberLogger::get_instance()->info("IO:GRAPHICS:select_camera(x1={},y1={},x2={},y2={})",
                                       _bbox.get_rect().x1, _bbox.get_rect().y1, _bbox.get_rect().x2, _bbox.get_rect().y2);
    BomberLogger::get_instance()->info("IO:GRAPHICS:select_camera(zoom={},{})", _x_scale_factor, _y_scale_factor);*/
}

void BomberGraphicsRenderer::clear()
{
    SDL_RenderClear(_renderer);
}

void BomberGraphicsRenderer::show_window()
{
    SDL_ShowWindow(_window);
}

void BomberGraphicsRenderer::hide_window()
{
    SDL_HideWindow(_window);
}

void BomberGraphicsRenderer::display()
{
    SDL_RenderPresent(_renderer);
}



unique_ptr<BomberTexture> BomberGraphicsRenderer::load_texture(BomberImg *img)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, img->get_surface());

    if (texture == nullptr)
    {
        throw BomberTextureLoadException("Error while loading texture");
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    auto result = make_unique<BomberTexture>(texture, img->get_surface()->w, img->get_surface()->h);
    return std::move(result);
}

BomberSpriteSheet::BomberSpriteSheet(const string &filename, shared_ptr<BomberImg> img)
{
    _sp_filename = filename;
    _sp_surface = img;
}

BomberSpriteSheet::~BomberSpriteSheet()
{
}

shared_ptr<BomberSpriteSheet> BomberSpriteSheet::load_from_png(const string &filename)
{
    SDL_Surface *surface = IMG_Load(filename.c_str());
    SDL_Surface *norm_surf = SDL_ConvertSurfaceFormat(
        surface,
        SDL_PIXELFORMAT_RGBA32,
        0);
    SDL_FreeSurface(surface);
    if (surface == nullptr)
    {
        stringstream ss;
        ss << "Error while loading spritesheet from " << filename;
        throw BomberSpriteSheetLoadException(ss.str());
    }
    return make_shared<BomberSpriteSheet>(filename, make_unique<BomberImg>(norm_surf));
}

shared_ptr<BomberImg> BomberSpriteSheet::load(int x, int y, int width, int height)
{
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
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(
        0,
        width,
        height,
        32,
        SDL_PIXELFORMAT_RGBA32);

    if (surface == nullptr)
    {
        stringstream ss;
        ss << "Error while loading tile from " << _sp_filename;
        throw BomberSpriteSheetLoadException(ss.str());
    }

    SDL_BlitSurface(_sp_surface->get_surface(), &rect, surface, &dst_rect);
    BomberLogger::get_instance()->debug("GAME:ENGINE:ASSETS:ASSET:spritesheet:load({},{},{},{}) - END", x, y, width, height);
    return make_shared<BomberImg>(surface);
}