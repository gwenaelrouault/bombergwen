#include "game_entity.h"
#include "bomber_logger.h"

void Entity::init(BomberGraphicsRenderer *renderer)
{
    _sprite->init(renderer);
    _sprite->set_current_state("idle");
}

void Entity::update(int elapsed_ms)
{
    _sprite->update(elapsed_ms);
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

int Hero::on_DOWN()
{
    int to_move = 0;
    if (_sprite->get_current_state()->get_name() != "walk_down")
    {
        if (_sprite->get_current_state()->get_name() == "idle")
        {
            _sprite->set_current_state("walk_down");
        }
        else
        {
            _sprite->set_current_state("idle");
        }
    }
    else
    {
        to_move = _speed;
    }
    if (to_move)
    {
        _sprite->move(0, to_move);
    }
    return to_move;
}

int Hero::on_UP()
{
    int to_move = 0;
    if (_sprite->get_current_state()->get_name() != "walk_up")
    {
        if (_sprite->get_current_state()->get_name() == "idle_up")
        {
            _sprite->set_current_state("walk_up");
        }
        else
        {
            _sprite->set_current_state("idle_up");
        }
    }
    else
    {
        to_move = -1 * _speed;
    }
    if (to_move)
    {
        _sprite->move(0, to_move);
    }
    return to_move;
}

int Hero::on_RIGHT()
{
    int to_move = 0;
    if (_sprite->get_current_state()->get_name() != "walk_right")
    {
        if (_sprite->get_current_state()->get_name() == "idle_right")
        {
            _sprite->set_current_state("walk_right");
        }
        else
        {
            _sprite->set_current_state("idle_right");
        }
    }
    else
    {
        to_move = _speed;
    }
    if (to_move)
    {
        _sprite->move(to_move, 0);
    }
    return to_move;
}

int Hero::on_LEFT()
{
    int to_move = 0;
    if (_sprite->get_current_state()->get_name() != "walk_left")
    {
        if (_sprite->get_current_state()->get_name() == "idle_left")
        {
            _sprite->set_current_state("walk_left");
        }
        else
        {
            _sprite->set_current_state("idle_left");
        }
    }
    else
    {
        to_move = -1 * _speed;
    }
    if (to_move)
    {
        _sprite->move(to_move, 0);
    }
    return to_move;
}