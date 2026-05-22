#include "levels.h"
#include "bomber_logger.h"

ostream &operator<<(std::ostream &os, const Level &s)
{
    os << "Level(" << s._name << ")" << endl;
    return os;
}

void LevelTile::load_texture(BomberGraphicsRenderer *renderer)
{
    _texture = renderer->load_texture(_img.get());
}

void LevelTile::draw(BomberGraphicsRenderer *renderer)
{
    //cout << "DRAW TILE(" << _column << "," << _row << ")" << endl;
    renderer->draw(_texture.get(), _coords);
}

Level::Level(const string &name,
             int cell_width, int cell_height,
             int columns, int rows,
             shared_ptr<BomberBBox> default_camera,
             const map<int, TTile_material> &tiles_material,
             const vector<shared_ptr<BomberImg>> &tiles) : _dimensions(make_unique<LevelDimensions>(cell_width, cell_height, columns, rows)),
                                                           _default_camera(default_camera),
                                                           DisplayableItem(name)
{
    int row = 0;
    int col = 0;
    int index = 0;
    for (auto tile_img : tiles)
    {  
        auto material = tiles_material.at(index++);
        auto tile = make_unique<LevelTile>(tile_img, row, col, material);
        _tiles.push_back(std::move(tile));
        if (++col >= columns)
        {
            col = 0;
            if (++row >= rows)
            {
                break;
            }
        }
    }
}

Level::~Level()
{
}

bool Level::is_inside(const BomberRect &rect)
{
    return (rect.x1 >= 0 && rect.y1 >= 0 && rect.x2 <= _dimensions->get_width() && rect.y2 <= _dimensions->get_height());
}

void Level::init(BomberGraphicsRenderer *renderer)
{
    BomberLogger::get_instance()->info("GAME:ENGINE:LEVEL:{}:init - START", _name);
    int mem_size_bytes = 0;
    for (int i = 0; i < _tiles.size(); i++)
    {
        auto tile = _tiles.at(i).get();
        tile->load_texture(renderer);
        mem_size_bytes += tile->get_mem_size();
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:LEVEL:{}:init(loaded={} bytes) - END", _name, mem_size_bytes);
}

bool Level::update(int elapsed_ms)
{
    (void) elapsed_ms;
    //cout << "update level" << _name << endl;
    return false;
}

void Level::draw(BomberGraphicsRenderer *renderer)
{
    //cout << "draw level(" << _name << ")" << endl;
    for (int i = 0; i < _tiles.size(); i++)
    {
        _tiles.at(i)->draw(renderer);
    }
}

void LevelsRepository::dump()
{
    cout << "loaded levels=" << _items.size() << endl;
    for (auto &level_it : _items)
    {
        auto level = level_it.second;
        cout << *level.get() << endl;
    }
}

BomberCoordinates Level::get_tile_coords(const BomberCoordinates &coords)
{
    int x = _dimensions->get_cell_width() * coords.get_x();
    int y = _dimensions->get_cell_height() * coords.get_y();
    return BomberCoordinates(x, y);
}