#pragma once

#include <string>
#include <memory>
#include "bomber_exceptions.h"
#include "bomber_io_common.h"

class SDL_Surface;
class SDL_Texture;
class SDL_Renderer;
class SDL_Window;

using namespace std;

class BomberBBox
{
public:
    BomberBBox(int x, int y, int width, int height, int screen_width, int screen_height)
        : _coords(x, y), _dimensions(width, height), _screen_dimensions(screen_width, screen_height) {}
    BomberBBox() : _coords(0, 0), _dimensions(0, 0), _screen_dimensions(0, 0) {

    }
    ~BomberBBox() {}

    int get_x() const { return _coords.get_x(); }
    int get_y() const { return _coords.get_y(); }

    const BomberDimensions& get_dimensions() { return _dimensions; }
    const BomberDimensions& get_screen_dimensions() { return _screen_dimensions; }

    BomberRect get_rect() { return _rect; }

    void set_position(const BomberCoordinates &coords);

    void set_dimension(int width, int height);

    const BomberCoordinates &get_coords()
    {
        return _coords;
    }

private:
    BomberCoordinates _coords;
    BomberDimensions _dimensions;
    BomberDimensions _screen_dimensions;
    BomberRect _rect;

    void compute_rect();
};

class BomberImg
{
public:
    BomberImg(SDL_Surface *surface);
    ~BomberImg();

    SDL_Surface *get_surface();

    int get_width() const { return _width; }
    int get_height() const { return _height; }

    int size_bytes() const { return _bytes; }

private:
    SDL_Surface *_surface;
    int _width;
    int _height;
    int _bytes;
};

class BomberTextureLoadException : public BomberException
{
public:
    BomberTextureLoadException(const std::string &msg) : BomberException(msg) {}
};

class BomberTexture
{
public:
    BomberTexture(SDL_Texture *texture, int width, int height);
    ~BomberTexture();

    SDL_Texture *get_texture();

    void unload_texture();

    int get_width() const { return _width; }

    int get_height() const { return _height; }

private:
    SDL_Texture *_texture;
    int _width;
    int _height;
};

class BomberGraphicsRenderer
{
public:
    BomberGraphicsRenderer(SDL_Renderer *renderer, int screen_width, int screen_height, SDL_Window *window);
    ~BomberGraphicsRenderer();

    unique_ptr<BomberTexture> load_texture(BomberImg *img);

    void draw(BomberTexture *texture, BomberCoordinates &coords);

    const BomberBBox& get_bbox() { return _bbox; }

    void clear();

    void display();

    void select_camera(BomberBBox *bbox);

    void show_window();
    void hide_window();

    static unique_ptr<BomberGraphicsRenderer> create_renderer(int screen_width, int screen_height);

private:
    SDL_Renderer *_renderer;
    SDL_Window *_window;
    int _screen_width;
    int _screen_height;
    double _x_scale_factor;
    double _y_scale_factor;
    int _screen_x_offset;
    int _screen_y_offset;
    BomberBBox _bbox;
};

class BomberSpriteSheetLoadException : public BomberException
{
public:
    BomberSpriteSheetLoadException(const std::string &msg) : BomberException(msg) {}
};

class BomberSpriteSheet
{
public:
    BomberSpriteSheet(const string &filename, shared_ptr<BomberImg> img);
    virtual ~BomberSpriteSheet();

    static shared_ptr<BomberSpriteSheet> load_from_png(const string &filename);
    shared_ptr<BomberImg> load(int x, int y, int width, int height);

private:
    string _sp_filename;
    shared_ptr<BomberImg> _sp_surface;
};
