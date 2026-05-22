#include "hero.h"
#include "levels.h"

THeroState HeroStateIdleDown::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_WALK_DOWN;
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_IDLE_UP;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_IDLE_LEFT;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateIdleUp::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_IDLE_DOWN;
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_WALK_UP;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_IDLE_LEFT;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateIdleLeft::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_IDLE_DOWN;
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_IDLE_UP;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_WALK_LEFT;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateIdleRight::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_IDLE_DOWN;
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_IDLE_UP;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_IDLE_LEFT;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_WALK_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateWalkDown::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_IDLE_UP;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_IDLE_LEFT;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateWalkUp::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_IDLE_DOWN;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_IDLE_LEFT;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateWalkLeft::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_IDLE_DOWN;
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_IDLE_UP;
    case TEntityEvent::ENTITY_RIGHT:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateWalkRight::get_next_state(TEntityEvent evt)
{
    switch (evt)
    {
    case TEntityEvent::ENTITY_DOWN:
        return THeroState::STATE_IDLE_DOWN;
    case TEntityEvent::ENTITY_UP:
        return THeroState::STATE_IDLE_UP;
    case TEntityEvent::ENTITY_LEFT:
        return THeroState::STATE_IDLE_LEFT;
    default:
        return get_id();
    }
}

THeroState HeroStateDie::get_next_state(TEntityEvent evt)
{
    return get_id();
}

Hero::Hero(shared_ptr<SpritesRepository> sprites, const string &name) : _current_state(THeroState::STATE_IDLE_DOWN), Entity(name, sprites, 2)
{
    auto idle_up_state = make_unique<HeroStateIdleUp>();
    auto idle_down_state = make_unique<HeroStateIdleDown>();
    auto idle_right_state = make_unique<HeroStateIdleRight>();
    auto idle_left_state = make_unique<HeroStateIdleLeft>();
    auto walk_up_state = make_unique<HeroStateWalkUp>();
    auto walk_down_state = make_unique<HeroStateWalkDown>();
    auto walk_right_state = make_unique<HeroStateWalkRight>();
    auto walk_left_state = make_unique<HeroStateWalkLeft>();
    auto die_state = make_unique<HeroStateDie>();

    _states.insert({idle_up_state->get_id(), ::move(idle_up_state)});
    _states.insert({idle_down_state->get_id(), ::move(idle_down_state)});
    _states.insert({idle_right_state->get_id(), ::move(idle_right_state)});
    _states.insert({idle_left_state->get_id(), ::move(idle_left_state)});

    _states.insert({walk_up_state->get_id(), ::move(walk_up_state)});
    _states.insert({walk_down_state->get_id(), ::move(walk_down_state)});
    _states.insert({walk_right_state->get_id(), ::move(walk_right_state)});
    _states.insert({walk_left_state->get_id(), ::move(walk_left_state)});

    _states.insert({die_state->get_id(), ::move(die_state)});
}

void Hero::on_event(TEntityEvent evt)
{
    auto next_state_id = _states[_current_state]->get_next_state(evt);
    if (next_state_id != _current_state)
    {
        auto next_state_name = _states[next_state_id]->get_name();
        _sprite->set_current_state(next_state_name);
        _current_state = next_state_id;
        _velocity = _states[_current_state]->get_velocity();
    }
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