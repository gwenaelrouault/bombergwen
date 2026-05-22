#pragma once

#include "sprites.h"

using namespace std;

typedef enum {
    ENTITY_UP, ENTITY_DOWN, ENTITY_LEFT, ENTITY_RIGHT
} TEntityEvent;

typedef struct {
    int x_offset;
    int y_offset;
} TEntityVelocity;

class Entity
{
public:
    Entity(const string &name, shared_ptr<SpritesRepository> sprites)
        : _sprite(sprites->get(name)), _x(0), _y(0), _speed(0), _velocity({0,0}) {}
    Entity(const string &name, shared_ptr<SpritesRepository> sprites, int speed)
        : _sprite(sprites->get(name)), _x(0), _y(0), _speed(speed) {}
    virtual ~Entity() {}

    int get_speed() const { return _speed; }

    virtual void init(BomberGraphicsRenderer *renderer);

    bool update(int elapsed_ms);
    void draw(BomberGraphicsRenderer *renderer);
    void move(int x_offset, int y_offset);

    void set_position(const BomberCoordinates &coords);
    void set_velocity(int xoffset, int yoffset);

    const TEntityVelocity& get_velocity() { return _velocity; }

    const BomberCoordinates & get_position() { return _sprite->get_coords(); }

protected:
    shared_ptr<Sprite> _sprite;
    int _x;
    int _y;
    int _speed;
    TEntityVelocity _velocity;
};


