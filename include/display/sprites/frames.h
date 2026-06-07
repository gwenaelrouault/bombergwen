#pragma once

#include "display_items.h"
#include "assets_def.h"

class SpriteFrame
{
public:
    SpriteFrame(const SpriteFrame& frame);
    SpriteFrame(int width, int height, int duration, int src_x, int src_y, shared_ptr<BomberImg> img)
        : _width(width), _height(height), _duration(duration), _src_x(src_x), _src_y(src_y), _img(img), _texture(nullptr) {}
    ~SpriteFrame() {}

    int get_width() { return _width; }
    int get_height() { return _height; }
    int get_duration() { return _duration; }

    shared_ptr<BomberImg> get_img() { return _img; }
    shared_ptr<BomberTexture> get_texture() { return _texture; }

    void load_texture(BomberGraphicsRenderer *renderer);

    shared_ptr<SpriteFrame> clone();

    friend ostream &operator<<(std::ostream &os, const SpriteFrame &p);

private:
    int _width;
    int _height;
    int _duration;
    int _src_x;
    int _src_y;
    shared_ptr<BomberImg> _img;
    shared_ptr<BomberTexture> _texture;
};