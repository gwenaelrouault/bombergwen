#pragma once

#include "sprites.h"

class ObjectRepository : public DisplayableItemsRepository<Sprite>
{
public:
    ObjectRepository() : DisplayableItemsRepository<Sprite>() {}
    ~ObjectRepository() {}

    virtual void dump();
};