#pragma once
#include "display_items.h"

typedef enum
{
    DECO,
    GROUND,
    PLOT
} TTile_material;

class LevelTile
{
public:
    LevelTile(shared_ptr<BomberImg> img, int grid_row, int grid_column, TTile_material material)
        : _img(img), _row(grid_row), _column(grid_column), _texture(nullptr), _coords(grid_column * img->get_width(), grid_row * img->get_height()), _material(material) {}
    ~LevelTile() {}

    void load_texture(BomberGraphicsRenderer *renderer);

    const BomberCoordinates &get_coords() const { return _coords; }

    int get_mem_size() const { return _img != nullptr ? _img->size_bytes() : 0; }

    BomberTexture *get_texture() { return _texture.get(); }

    TTile_material get_material() const { return _material; }

    void draw(BomberGraphicsRenderer *renderer);

private:
    shared_ptr<BomberImg> _img;
    int _row;
    int _column;
    unique_ptr<BomberTexture> _texture;
    BomberCoordinates _coords;
    TTile_material _material;
};