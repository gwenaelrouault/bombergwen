
#include "world.h"
#include "bomber_logger.h"
#include <sstream>

void World::load(shared_ptr<SpritesRepository> sprites, shared_ptr<LevelsRepository> levels)
{
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:load - START");
    _sprites = sprites;
    _levels = levels;
    _hero = make_shared<Hero>(sprites);
    _entities.push_back(_hero);
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:load - END");
}

void World::select_level(const string &name, BomberGraphicsRenderer *renderer)
{
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:select level {}", name);
    if (!_levels->exists(name))
    {
        stringstream ss;
        ss << "Cannot select level " << name;
        throw NoLevelException(ss.str());
    }
    _selected_level = _levels->get(name);
    BomberCoordinates hero_start_position_grid(2, 2);
    BomberCoordinates hero_start_position = _selected_level->get_tile_coords(hero_start_position_grid);
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:POS HERO {},{}", hero_start_position.get_x(), hero_start_position.get_y());
    _hero->set_position(hero_start_position);
    renderer->select_camera(_selected_level->get_default_camera().get());
}

void World::init(BomberGraphicsRenderer *renderer)
{
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:init - START");
    if (_selected_level != nullptr)
    {
        _selected_level->init(renderer);
    }
    for (auto &entity : _entities)
    {
        entity->init(renderer);
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:init - END");
}

void World::update(int elapsed_ms)
{
    if (_selected_level != nullptr)
    {
        _selected_level->update(elapsed_ms);
    }
    for (auto &entity : _entities)
    {
        entity->update(elapsed_ms);
    }
}

void World::draw(BomberGraphicsRenderer *renderer)
{
    if (_selected_level != nullptr)
    {
        _selected_level->draw(renderer);
    }
    for (auto &entity : _entities)
    {
        entity->draw(renderer);
    }
}

void World::on_UP(BomberGraphicsRenderer *renderer)
{
    int step_up = _hero->on_UP();
    if (step_up != 0)
    {
        auto camera = renderer->get_bbox();
        BomberCoordinates camera_new_coords(camera.get_coords().get_x(), camera.get_coords().get_y() + step_up);
        camera.set_position(camera_new_coords);
        if (_selected_level->is_inside(camera.get_rect()))
        {
            renderer->select_camera(&camera);
        }
    }
}

void World::on_DOWN(BomberGraphicsRenderer *renderer)
{
    int step_down = _hero->on_DOWN();
    if (step_down != 0 && _selected_level != nullptr)
    {
        auto camera = renderer->get_bbox();
        BomberCoordinates camera_new_coords(camera.get_coords().get_x(), camera.get_coords().get_y() + step_down);
        camera.set_position(camera_new_coords);
        if (_selected_level->is_inside(camera.get_rect()))
        {
            renderer->select_camera(&camera);
        }
    }
}

void World::on_RIGHT(BomberGraphicsRenderer *renderer)
{
    int step_right = _hero->on_RIGHT();
    if (step_right != 0 && _selected_level != nullptr)
    {
        auto camera = renderer->get_bbox();
        BomberCoordinates camera_new_coords(camera.get_coords().get_x() + step_right, camera.get_coords().get_y());
        camera.set_position(camera_new_coords);
        if (_selected_level->is_inside(camera.get_rect()))
        {
            renderer->select_camera(&camera);
        }
    }
}

void World::on_LEFT(BomberGraphicsRenderer *renderer)
{
    int step_left = _hero->on_LEFT();
    if (step_left != 0 && _selected_level != nullptr)
    {
        auto camera = renderer->get_bbox();
        BomberCoordinates camera_new_coords(camera.get_coords().get_x() + step_left, camera.get_coords().get_y());
        camera.set_position(camera_new_coords);
        BomberLogger::get_instance()->info("CAMERA({},{},{},{})", camera.get_rect().x1, camera.get_rect().y1, camera.get_rect().x2, camera.get_rect().y2);

        if (_selected_level->is_inside(camera.get_rect()))
        {
            renderer->select_camera(&camera);
        }
    }
}