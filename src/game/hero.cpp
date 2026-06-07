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
    case TEntityEvent::ENTITY_DOWN_CANCEL:
        return THeroState::STATE_IDLE_DOWN;
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
    case TEntityEvent::ENTITY_UP_CANCEL:
        return THeroState::STATE_IDLE_UP;
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
    case TEntityEvent::ENTITY_LEFT_CANCEL:
        return THeroState::STATE_IDLE_LEFT;
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
    case TEntityEvent::ENTITY_RIGHT_CANCEL:
        return THeroState::STATE_IDLE_RIGHT;
    default:
        return get_id();
    }
}

THeroState HeroStateDie::get_next_state(TEntityEvent evt)
{
    return get_id();
}

Hero::Hero(shared_ptr<SpritesRepository> sprites, const string &name) : _current_state(THeroState::STATE_IDLE_DOWN), Entity(name, sprites)
{
    auto idle_up_state = make_shared<HeroStateIdleUp>();
    auto idle_down_state = make_shared<HeroStateIdleDown>();
    auto idle_right_state = make_shared<HeroStateIdleRight>();
    auto idle_left_state = make_shared<HeroStateIdleLeft>();
    auto walk_up_state = make_shared<HeroStateWalkUp>();
    auto walk_down_state = make_shared<HeroStateWalkDown>();
    auto walk_right_state = make_shared<HeroStateWalkRight>();
    auto walk_left_state = make_shared<HeroStateWalkLeft>();
    auto die_state = make_shared<HeroStateDie>();

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
    if (evt == TEntityEvent::ENTITY_ACTION)
    {
        put_bomb();
    }
}

void Hero::put_bomb()
{
    auto current_grid_coords = _level->get_grid_coords(_sprite->get_coords());
    

}
