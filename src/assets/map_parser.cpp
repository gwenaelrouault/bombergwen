#include "map_parser.h"
#include "nlohmann/json.hpp"
#include "bomber_logger.h"
#include "bomber_graphics.h"
#include <fstream>

ostream &operator<<(std::ostream &os, const LevelGameMap &m)
{
    os << "Map(name:" << m._name
       << "," << m._columns << "," << m._rows << "," << m._cells.size() << ")" << endl;
    os << "{" << endl;
    int y = 0;
    int x = 0;
    for (int i = 0; i < m._size; i++)
    {
        if (x == 0)
        {
            os << "\t";
        }
        os << m._cells[i] << " ";
        if (++x >= m._rows)
        {
            x = 0;
            y++;
            os << endl;
        }
    }
    os << "}" << endl;
    return os;
}

shared_ptr<LevelGameMap> LevelGameMap::parse(shared_ptr<AseSpritesheet> spritesheet, const string &filename)
{
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:LEVEL:MAP:{}:load - START", filename.c_str());
    auto frames = spritesheet->get_frames();
    std::ifstream json_file(filename);
    auto parsed_json = nlohmann::json::parse(json_file);
    string name = parsed_json.at("name");
    int columns = parsed_json.at("columns");
    int rows = parsed_json.at("rows");
    nlohmann::json json_cells = parsed_json.at("map");
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:LEVEL:MAP:{}:load dimensions({}:rows={},columns={})",
                                       filename.c_str(), name.c_str(), rows, columns);
    int i = 0;
    vector<int> cells;
    for (auto cell : json_cells)
    {
        if (frames.size() < cell)
        {
            throw MapParseException("Invalid cell");
        }
        cells.push_back(cell);
    }
    for(int i = 0; i < cells.size(); i++) {
        cout << cells[i];
    }
    cout << endl;
    nlohmann::json json_camera = parsed_json.at("camera");
    int x_camera = json_camera.at("x");
    int y_camera = json_camera.at("y");
    int width_camera = json_camera.at("width");
    int height_camera = json_camera.at("height");
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:LEVEL:MAP:{}:load camera({},{},{},{})",
                                       filename.c_str(), x_camera, y_camera, width_camera, height_camera);
    auto level_camera = make_shared<BomberBBox>(x_camera, y_camera, width_camera, height_camera,0,0);
    auto result = make_shared<LevelGameMap>(name, spritesheet, columns, rows, cells, level_camera);
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:LEVEL:MAP:{}:load - END {}", filename.c_str(), result->_cells.size());
    return result;
}

void LevelGameMap::dump()
{
    cout << *this;
}