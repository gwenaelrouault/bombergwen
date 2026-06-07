#pragma once

#include "game_entity.h"


#define STATE_DIE_NAME "DIE"

class Level;

typedef enum
{
    STATE_IDLE_UP,
    STATE_IDLE_DOWN,
    STATE_IDLE_LEFT,
    STATE_IDLE_RIGHT,
    STATE_WALK_UP,
    STATE_WALK_DOWN,
    STATE_WALK_LEFT,
    STATE_WALK_RIGHT,
    STATE_DIE
} THeroState;

class HeroState
{
public:
    HeroState(const string &name, THeroState id, const TEntityVelocity& velocity) : _name(name), _id(id), _velocity(velocity) {
    }
    virtual ~HeroState() {}

    const string &get_name() const { return _name; }

    THeroState get_id() const { return _id; }

    virtual THeroState get_next_state(TEntityEvent evt) = 0;

    const TEntityVelocity& get_velocity() { return _velocity; }

private:
    string _name;
    THeroState _id;
    TEntityVelocity _velocity;
};

class HeroStateIdleUp : public HeroState
{
public:
    HeroStateIdleUp() : HeroState(STATE_IDLE_UP_NAME, THeroState::STATE_IDLE_UP, TEntityVelocity({0,0})) {}
    virtual ~HeroStateIdleUp() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateIdleDown : public HeroState
{
public:
    HeroStateIdleDown() : HeroState(STATE_IDLE_DOWN_NAME, THeroState::STATE_IDLE_DOWN, TEntityVelocity({0,0})) {}
    virtual ~HeroStateIdleDown() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateIdleRight : public HeroState
{
public:
    HeroStateIdleRight() : HeroState(STATE_IDLE_RIGHT_NAME, THeroState::STATE_IDLE_RIGHT, TEntityVelocity({0,0})) {}
    virtual ~HeroStateIdleRight() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateIdleLeft : public HeroState
{
public:
    HeroStateIdleLeft() : HeroState(STATE_IDLE_LEFT_NAME, THeroState::STATE_IDLE_LEFT, TEntityVelocity({0,0})) {}
    virtual ~HeroStateIdleLeft() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateWalkUp : public HeroState
{
public:
    HeroStateWalkUp() : HeroState(STATE_WALK_UP_NAME, THeroState::STATE_WALK_UP, TEntityVelocity({0,-2})) {}
    virtual ~HeroStateWalkUp() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateWalkDown : public HeroState
{
public:
    HeroStateWalkDown() : HeroState(STATE_WALK_DOWN_NAME, THeroState::STATE_WALK_DOWN, TEntityVelocity({0,2})) {}
    virtual ~HeroStateWalkDown() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateWalkRight : public HeroState
{
public:
    HeroStateWalkRight() : HeroState(STATE_WALK_RIGHT_NAME, THeroState::STATE_WALK_RIGHT, TEntityVelocity({2,0})) {}
    virtual ~HeroStateWalkRight() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateWalkLeft : public HeroState
{
public:
    HeroStateWalkLeft() : HeroState(STATE_WALK_LEFT_NAME, THeroState::STATE_WALK_LEFT, TEntityVelocity({-2,0})) {}
    virtual ~HeroStateWalkLeft() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class HeroStateDie : public HeroState
{
public:
    HeroStateDie() : HeroState(STATE_DIE_NAME, THeroState::STATE_DIE, TEntityVelocity({0,0})) {}
    virtual ~HeroStateDie() {}

    virtual THeroState get_next_state(TEntityEvent evt);
};

class Hero : public Entity
{
public:
    Hero(shared_ptr<SpritesRepository> sprites, const string& name);
    virtual ~Hero() {}

    THeroState get_current_state() const { return _current_state; }

    void on_event(TEntityEvent evt);

    void put_bomb();

private:
    THeroState _current_state;
    map<THeroState, shared_ptr<HeroState>> _states;
};

class MainHero : public Hero
{
public:
    MainHero(shared_ptr<SpritesRepository> sprites, const string& name) : Hero(sprites, name) {}
    virtual ~MainHero() {}

};