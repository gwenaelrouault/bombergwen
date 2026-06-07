#include "tiles.h"

void LevelTile::load_texture(BomberGraphicsRenderer *renderer)
{
    _texture = renderer->load_texture(_img.get());
}

void LevelTile::draw(BomberGraphicsRenderer *renderer)
{
    renderer->draw(_texture.get(), _coords);
}