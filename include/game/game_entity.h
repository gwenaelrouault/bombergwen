#pragma once

#include "sprites.h"
#include "levels.h"

using namespace std;

typedef enum {
    ENTITY_UP, ENTITY_DOWN, ENTITY_LEFT, ENTITY_RIGHT,
    ENTITY_UP_CANCEL, ENTITY_DOWN_CANCEL, ENTITY_LEFT_CANCEL, ENTITY_RIGHT_CANCEL,
    ENTITY_ACTION
} TEntityEvent;

typedef struct {
    int x_offset;
    int y_offset;
} TEntityVelocity;

constexpr int EPSILON_COLLIDERS = 4;

class Entity
{
public:
    Entity(const string &name, shared_ptr<SpritesRepository> sprites)
        : _name(name), _sprite(sprites->get_copy(name)),  _velocity({0,0}), _level(nullptr) {}
    virtual ~Entity() {}

    virtual void init(shared_ptr<Level> level, BomberGraphicsRenderer *renderer);

    bool update(Level* level,int elapsed_ms);
    void draw(BomberGraphicsRenderer *renderer);
    bool move(Level* level, int x_offset, int y_offset);

    void set_position(const BomberCoordinates &coords);
    void set_velocity(int xoffset, int yoffset);

    const TEntityVelocity& get_velocity() { return _velocity; }

    const BomberCoordinates & get_position() { return _sprite->get_coords(); }

    const string& get_name() const { return _name; }

    bool has_speed();

protected:
    string _name;
    shared_ptr<Sprite> _sprite;
    TEntityVelocity _velocity;
    shared_ptr<Level> _level;

    bool can_move(Level* level, const BomberCoordinates& coords);
};


