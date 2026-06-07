#include "levels.h"
#include "bomber_logger.h"

ostream &operator<<(std::ostream &os, const Level &s)
{
    os << "Level(" << s._name << ")" << endl;
    return os;
}

Level::Level(const string &name,
             int cell_width, int cell_height,
             int columns, int rows,
             shared_ptr<BomberBBox> default_camera,
             const vector<shared_ptr<LevelCell>> &tiles) : _dimensions(make_unique<LevelDimensions>(cell_width, cell_height, columns, rows)),
                                                           _default_camera(default_camera),
                                                           DisplayableItem(name)
{
    _columns = columns;
    _rows = rows;
    int row = 0;
    int col = 0;
    int index = 0;
    for (auto cell : tiles)
    {
        auto tile = make_shared<LevelTile>(cell->get_img(), row, col, cell->get_material());
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


Level::Level(const Level& level) : DisplayableItem(level)
{
    _columns = level._columns;
    _rows = level._rows;
    _size = level._size;
    _dimensions = make_unique<LevelDimensions>(level._dimensions->get_cell_width(), level._dimensions->get_cell_height(), level._dimensions->get_columns(), level._dimensions->get_rows());
    for(auto tile : level._tiles)
    {
        _tiles.push_back(tile);
    }
    _default_camera = level._default_camera;
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
    (void)elapsed_ms;
    return false;
}

void Level::draw(BomberGraphicsRenderer *renderer)
{
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

BomberCoordinates Level::get_tile_coords(const GridCoordinates &coords)
{
    double x = _dimensions->get_cell_width() * coords.get_column();
    double y = _dimensions->get_cell_height() * coords.get_row();
    return BomberCoordinates(x, y);
}

GridCoordinates Level::get_grid_coords(const BomberCoordinates &coords)
{
    int x = (int)round(coords.get_x() / _dimensions->get_cell_width());
    int y = (int)round(coords.get_y() / _dimensions->get_cell_height());
    cout << "X " << x << "coordx " << coords.get_x() << "coordy " << coords.get_y() << endl;
    cout << "Y " << y << endl;
    return GridCoordinates(y, x);
}

TTile_material Level::get_tile_material(const GridCoordinates &grid_coords)
{
    
    int index = grid_coords.get_row() * _columns + grid_coords.get_column();
    cout << "MAT " << index << "," << grid_coords.get_row() << "," << grid_coords.get_column() << std::endl;
    return _tiles[index]->get_material();
}

shared_ptr<Level> Level::clone()
{
    return make_shared<Level>(*this);
}