#pragma once

#include "levels.h"
#include "sprites.h"
#include "hero.h"
#include "bomber_exceptions.h"
#include "bomber_input.h"

class NoLevelException : public BomberException
{
public:
    NoLevelException(const std::string &msg) : BomberException(msg) {}
};

class World
{
public:
    World() : _sprites(nullptr), _levels(nullptr), _hero(nullptr), _selected_level(nullptr) {}
    ~World() {}

    void load(shared_ptr<SpritesRepository> sprites, shared_ptr<LevelsRepository> levels);

    void select_level(const string &name, BomberGraphicsRenderer *renderer);

    void init(BomberGraphicsRenderer *renderer);

    void update(BomberGraphicsRenderer *renderer, int elapsed_ms);

    void draw(BomberGraphicsRenderer *renderer);

    void on_event(T_BomberKeyEvent event);

private:
    shared_ptr<SpritesRepository> _sprites;
    shared_ptr<LevelsRepository> _levels;
    shared_ptr<Level> _selected_level;
    shared_ptr<MainHero> _hero;
    vector<shared_ptr<Hero>> _ennemies;
    vector<shared_ptr<Entity>> _entities;
};
