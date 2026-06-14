#pragma once

#include "sprites.h"

class ObjectRepository : public SpritesRepository
{
public:
    ObjectRepository() : SpritesRepository() {}
    ~ObjectRepository() {}

    virtual void dump();
};