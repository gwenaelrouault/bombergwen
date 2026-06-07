
#include "world.h"
#include "bomber_logger.h"
#include <sstream>

void World::load(shared_ptr<SpritesRepository> sprites, shared_ptr<LevelsRepository> levels, shared_ptr<ObjectRepository> objects)
{
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:load - START");
    _sprites = sprites;
    _levels = levels;
    _objects = objects;
    _hero = make_shared<MainHero>(sprites, NAME_HERO);
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
    GridCoordinates hero_start_position_grid(2, 2);
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
        entity->init(_selected_level, renderer);
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:WORLD:init - END");
}

void World::update(BomberGraphicsRenderer *renderer, int elapsed_ms)
{
    if (_selected_level != nullptr)
    {
        _selected_level->update(elapsed_ms);
    }
    for (auto &entity : _ennemies)
    {
        entity->update(_selected_level.get(), elapsed_ms);
    }
    if (_hero->update(_selected_level.get(),elapsed_ms))
    {
        auto velocity = _hero->get_velocity();
        auto camera = renderer->get_bbox();
        BomberCoordinates camera_new_coords(camera.get_coords().get_x() + velocity.x_offset, camera.get_coords().get_y() + velocity.y_offset);
        camera.set_position(camera_new_coords);
        if (_selected_level->is_inside(camera.get_rect()))
        {
            renderer->select_camera(&camera);
        }
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

void World::on_event(T_BomberKeyEvent event)
{
    switch (event)
    {
    case T_BomberKeyEvent::BOMBER_KEY_DOWN:
        _hero->on_event(TEntityEvent::ENTITY_DOWN);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_LEFT:
        _hero->on_event(TEntityEvent::ENTITY_LEFT);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_RIGHT:
        _hero->on_event(TEntityEvent::ENTITY_RIGHT);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_UP:
        _hero->on_event(TEntityEvent::ENTITY_UP);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_DOWN_CANCEL:
        _hero->on_event(TEntityEvent::ENTITY_DOWN_CANCEL);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_LEFT_CANCEL:
        _hero->on_event(TEntityEvent::ENTITY_LEFT_CANCEL);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_RIGHT_CANCEL:
        _hero->on_event(TEntityEvent::ENTITY_RIGHT_CANCEL);
        break;
    case T_BomberKeyEvent::BOMBER_KEY_UP_CANCEL:
        _hero->on_event(TEntityEvent::ENTITY_UP_CANCEL);
        break;
   case T_BomberKeyEvent::BOMBER_KEY_ACTION:
        _hero->on_event(TEntityEvent::ENTITY_ACTION);
        break; 
    
    default:
        BomberLogger::get_instance()->debug("GAME:ENGINE:WORLD:onevent ignored");
    }
}
