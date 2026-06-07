#include "frames.h"

ostream &operator<<(std::ostream &os, const SpriteFrame &f)
{
    os << "Frame(width:" << f._width << ",height:" << f._height << ",sp:" << f._src_x << "," << f._src_y << ")";
    return os;
}


SpriteFrame::SpriteFrame(const SpriteFrame& frame)
{
    _width = frame._width;
    _height = frame._height;
    _src_x = frame._src_x;
    _src_y = frame._src_y;
    _img = frame._img;
    _texture = nullptr;
}

void SpriteFrame::load_texture(BomberGraphicsRenderer *renderer)
{
    _texture = renderer->load_texture(_img.get());
}

shared_ptr<SpriteFrame> SpriteFrame::clone()
{
    return make_shared<SpriteFrame>(*this);
}