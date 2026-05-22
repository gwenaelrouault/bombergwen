#include "game_entity.h"
#include "bomber_logger.h"

void Entity::init(BomberGraphicsRenderer *renderer)
{
    _sprite->init(renderer);
    _sprite->set_current_state("idle");
}

bool Entity::update(int elapsed_ms)
{
    _sprite->update(elapsed_ms);
    if (_velocity.x_offset != 0 || _velocity.y_offset != 0)
    {
        move(_velocity.x_offset, _velocity.y_offset);
        return true;
    }
    return false;
}

void Entity::move(int x_offset, int y_offset)
{
    _sprite->move(x_offset, y_offset);
}

void Entity::draw(BomberGraphicsRenderer *renderer)
{
    _sprite->draw(renderer);
}

void Entity::set_position(const BomberCoordinates &coords)
{
    BomberLogger::get_instance()->info("SPRITE:SET_POS({})", coords.get_x(), coords.get_y());
    _sprite->set_position(coords);
}

void Entity::set_velocity(int xoffset, int yoffset)
{
    _velocity.x_offset = xoffset;
    _velocity.y_offset = yoffset;
}
