#pragma once

#include <iostream>
#include "display_items.h"
#include <vector>
#include "bomber_logger.h"

typedef enum {
    DECO,
    GROUND,
    PLOT
} TTile_material;

class GridCoordinates
{
public:
    GridCoordinates(int row, int col) : _row(row), _column(col) {}
    ~GridCoordinates() {}

    int get_row() const { return _row; }

    int get_column() const { return _column; }

private:
    int _row;
    int _column;
};

class LevelDimensions
{
public:
    LevelDimensions(int cell_width, int cell_height, int columns, int rows)
        : _cell_width(cell_width), _cell_height(cell_height),
          _columns(columns), _rows(rows), _size(rows * columns) {}
    ~LevelDimensions() {}

    int get_cell_width() const { return _cell_width; }

    int get_cell_height() const { return _cell_height; }

    int get_width() const { return _cell_width * _columns; }
    int get_height() const { return _cell_height * _rows; }

private:
    int _cell_width;
    int _cell_height;
    int _columns;
    int _rows;
    int _size;
};

class LevelCell
{
public:
    LevelCell(shared_ptr<BomberImg> img, TTile_material material) : _img(img), _material(material) {}
    ~LevelCell() {}

    shared_ptr<BomberImg> get_img() { return _img; }
    TTile_material get_material() { return _material; }
    
private:
    shared_ptr<BomberImg> _img;
    TTile_material _material;
};

class LevelTile
{
public:
    LevelTile(shared_ptr<BomberImg> img, int grid_row, int grid_column, TTile_material material)
        : _img(img), _row(grid_row), _column(grid_column), _texture(nullptr), _coords(grid_column * img->get_width(), grid_row * img->get_height()), _material(material)
    {
       // BomberLogger::get_instance()->info("PUT TILE(row={},colum,={}):{},{}", grid_row,grid_column,_x, _y);
    }
    ~LevelTile() {}

    void load_texture(BomberGraphicsRenderer* renderer);

    const BomberCoordinates& get_coords() const { return _coords; }

    int get_mem_size() const { return _img != nullptr ? _img->size_bytes() : 0; }

    BomberTexture* get_texture() { return _texture.get(); }

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

class Level : public DisplayableItem
{
public:
    Level(const string &name,
          int cell_width, int cell_height,
          int columns, int rows,
          shared_ptr<BomberBBox> default_camera,
          const vector<shared_ptr<LevelCell>> &tiles);
    virtual ~Level();

    virtual void init(BomberGraphicsRenderer *renderer);

    virtual bool update(int elapsed_ms);

    virtual void draw(BomberGraphicsRenderer *renderer);

    friend ostream &operator<<(std::ostream &os, const Level &p);

    shared_ptr<BomberBBox> get_default_camera() { return _default_camera; }

    BomberCoordinates get_tile_coords(const GridCoordinates& grid_coords);

    GridCoordinates get_grid_coords(const BomberCoordinates& coords);
    
    const LevelDimensions& get_dimension() { return *_dimensions.get(); }

    bool is_inside(const BomberRect& rect);

    int compute_size();

    TTile_material get_tile_material(const GridCoordinates& grid_coords);

private:
    int _columns;
    int _rows;
    int _size;
    unique_ptr<LevelDimensions> _dimensions;
    shared_ptr<BomberBBox> _default_camera;
    vector<unique_ptr<LevelTile>> _tiles;
};

class LevelsRepository : public DisplayableItemsRepository<Level>
{
public:
    LevelsRepository() : DisplayableItemsRepository<Level>() {}
    ~LevelsRepository() {}

    virtual void dump();
};
