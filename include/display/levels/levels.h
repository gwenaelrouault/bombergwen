#pragma once

#include <iostream>
#include "display_items.h"
#include <vector>
#include "bomber_logger.h"
#include "tiles.h"

class GridCoordinates
{
public:
    GridCoordinates(int row, int col) : _row(row), _column(col) {}
    ~GridCoordinates() {}

    int get_row() const { return _row; }

    int get_column() const { return _column; }


     bool operator==(const GridCoordinates& other) const {
        return _row == other._row && _column == other._column;
    }

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

    int get_columns() const { return _columns; }
    int get_rows() const { return _rows; }

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


class Level : public DisplayableItem
{
public:
    Level(const Level &level);
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

    BomberCoordinates get_tile_coords(const GridCoordinates &grid_coords);

    GridCoordinates get_grid_coords(const BomberCoordinates &coords);

    const LevelDimensions &get_dimension() { return *_dimensions.get(); }

    bool is_inside(const BomberRect &rect);

    int compute_size();

    TTile_material get_tile_material(const GridCoordinates &grid_coords);

    virtual shared_ptr<Level> clone();

private:
    int _columns;
    int _rows;
    int _size;
    unique_ptr<LevelDimensions> _dimensions;
    shared_ptr<BomberBBox> _default_camera;
    vector<shared_ptr<LevelTile>> _tiles;
};

class LevelsRepository : public DisplayableItemsRepository<Level>
{
public:
    LevelsRepository() : DisplayableItemsRepository<Level>() {}
    ~LevelsRepository() {}

    virtual void dump();
};
