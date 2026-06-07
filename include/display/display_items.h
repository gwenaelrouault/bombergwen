#pragma once

#include "bomber_graphics.h"
#include <string>
#include <memory>
#include <map>

using namespace std;


class DisplayableItem
{
public:
    DisplayableItem(const string &name) : _name(name) {}

    DisplayableItem(const DisplayableItem& item) {
        _name = item.get_name();
    }

    virtual ~DisplayableItem() {}

    virtual void init(BomberGraphicsRenderer *renderer) = 0;

    virtual bool update(int elapsed_ms) = 0;

    virtual void draw(BomberGraphicsRenderer* renderer) = 0;

    const string &get_name() const { return _name; }


protected:
    string _name;
};

template <typename T>
class DisplayableItemsRepository
{
public:
    DisplayableItemsRepository() {}
    virtual ~DisplayableItemsRepository() {}

    void add(const string& name, shared_ptr<T> item) {
        _items.insert({name, item});
    }

    shared_ptr<T> get_copy(const string& name) { return _items.at(name)->clone(); }

    shared_ptr<T> get(const string& name) { return _items.at(name); }

    bool exists(const string& name) { return _items.find(name) != _items.end(); }

    virtual void dump() = 0;

protected:
    map<string, shared_ptr<T>> _items;
};