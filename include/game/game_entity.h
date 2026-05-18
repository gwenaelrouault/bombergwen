#pragma once

#include "sprites.h"

using namespace std;

class Entity
{
public:
    Entity(const string &name, shared_ptr<SpritesRepository> sprites)
        : _sprite(sprites->get(name)), _x(0), _y(0), _speed(0) {}
    Entity(const string &name, shared_ptr<SpritesRepository> sprites, int speed)
        : _sprite(sprites->get(name)), _x(0), _y(0), _speed(speed) {}
    virtual ~Entity() {}

    int get_speed() const { return _speed; }

    virtual void init(BomberGraphicsRenderer *renderer);

    void update(int elapsed_ms);
    void draw(BomberGraphicsRenderer *renderer);
    void move(int x_offset, int y_offset);

    void set_position(const BomberCoordinates &coords);
    const BomberCoordinates & get_position() { return _sprite->get_coords(); }

protected:
    shared_ptr<Sprite> _sprite;
    int _x;
    int _y;
    int _speed;
};

class Hero : public Entity
{
public:
    Hero(shared_ptr<SpritesRepository> sprites) : Entity(NAME_HERO, sprites, 2) {}
    virtual ~Hero() {}

    int on_UP();
    int on_DOWN();
    int on_RIGHT();
    int on_LEFT();

private:
};

class Dino : public Entity
{
public:
    Dino(shared_ptr<SpritesRepository> sprites) : Entity(NAME_DINO, sprites) {}
    virtual ~Dino() {}

private:
};

class Dilo : public Entity
{
public:
    Dilo(shared_ptr<SpritesRepository> sprites) : Entity(NAME_DILO, sprites) {}
    virtual ~Dilo() {}

private:
};