#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "bomber_exceptions.h"
#include "ase_parser.h"
#include "bomber_graphics.h"

using namespace std;

class MapParseException : public BomberException
{
public:
    MapParseException(const std::string &msg) : BomberException(msg) {}
};

class LevelGameMap
{
public:
    LevelGameMap(
        const string &name,
        shared_ptr<AseSpritesheet> spritesheet,
        int columns, int rows,
        vector<int> cells,
        shared_ptr<BomberBBox> default_camera)
        : _name(name), _spritesheet(spritesheet), _columns(columns), _rows(rows), _size(rows * columns),
          _default_camera(default_camera)
    {
        _cells.reserve(cells.size());
        for (int i = 0; i < cells.size(); i++)
        {
            _cells.push_back(cells[i]);
        }
    }
    ~LevelGameMap() {}
    const string &get_name() const
    {
        return _name;
    }

    int get_columns() const
    {
        return _columns;
    }
    int get_rows() const
    {
        return _rows;
    }
    int get_size() const
    {
        return _size;
    }

    const int get_cell(int index) const { return _cells[index]; }

    shared_ptr<BomberBBox> get_default_camera() { return _default_camera; }

    static shared_ptr<LevelGameMap> parse(shared_ptr<AseSpritesheet> spritesheet, const string &filename);

    friend ostream &operator<<(std::ostream &os, const LevelGameMap &p);

    void dump();

private:
    string _name;
    shared_ptr<AseSpritesheet> _spritesheet;
    int _columns;
    int _rows;
    int _size;
    vector<int> _cells;
    shared_ptr<BomberBBox> _default_camera;
};
