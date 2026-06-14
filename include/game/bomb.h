#pragma once

#include "game_entity.h"
#include "bomber_object.h"


class Bomb : public Entity
{
public:
    Bomb(shared_ptr<ObjectRepository> objects, const string& name) : Entity(name, objects) {}
    ~Bomb() {}
private:
};

class BombFactory
{
public:
    BombFactory(shared_ptr<ObjectRepository> objects) : _objects(objects) {}
    ~BombFactory() {}

    shared_ptr<Bomb> build_bomb(const BomberCoordinates& coords);

private:
    shared_ptr<ObjectRepository> _objects; 
};