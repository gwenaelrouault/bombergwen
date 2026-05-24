#pragma once

#include "sprites.h"
#include "levels.h"

using namespace std;

typedef enum {
    ENTITY_UP, ENTITY_DOWN, ENTITY_LEFT, ENTITY_RIGHT,
    ENTITY_UP_CANCEL, ENTITY_DOWN_CANCEL, ENTITY_LEFT_CANCEL, ENTITY_RIGHT_CANCEL
} TEntityEvent;

typedef struct {
    int x_offset;
    int y_offset;
} TEntityVelocity;

class Entity
{
public:
    Entity(const string &name, shared_ptr<SpritesRepository> sprites)
        : _sprite(sprites->get(name)), _speed(0), _velocity({0,0}) {}
    Entity(const string &name, shared_ptr<SpritesRepository> sprites, int speed)
        : _sprite(sprites->get(name)), _speed(speed) {}
    virtual ~Entity() {}

    int get_speed() const { return _speed; }

    virtual void init(BomberGraphicsRenderer *renderer);

    bool update(Level* level,int elapsed_ms);
    void draw(BomberGraphicsRenderer *renderer);
    bool move(Level* level, int x_offset, int y_offset);

    void set_position(const BomberCoordinates &coords);
    void set_velocity(int xoffset, int yoffset);

    const TEntityVelocity& get_velocity() { return _velocity; }

    const BomberCoordinates & get_position() { return _sprite->get_coords(); }

    bool has_speed();

protected:
    shared_ptr<Sprite> _sprite;
    int _speed;
    TEntityVelocity _velocity;

    bool can_move(Level* level, const BomberCoordinates& coords);
};


