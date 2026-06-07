#pragma once

#include <vector>
#include <iostream>
#include "display_items.h"
#include "assets_def.h"
#include "frames.h"
#include "states.h"

class SpriteBoundingBox
{
public:
    SpriteBoundingBox(const string& name, int x, int y, int w, int h)
        : _name(name), _x(x), _y(y), _width(w), _height(h) {}

    SpriteBoundingBox(const SpriteBoundingBox& box);
    ~SpriteBoundingBox() {}

    const string& get_name() const { return _name; }
    int get_x() const { return _x; }
    int get_y() const { return _y; }
    int get_width() const { return _width; }
    int get_height() const { return _height; }

    shared_ptr<SpriteBoundingBox> clone();

private:
    string _name;
    int _x;
    int _y;
    int _width;
    int _height;
};



class Sprite : public DisplayableItem
{
public:
    Sprite(const string &name, vector<shared_ptr<SpriteState>> &states, vector<shared_ptr<SpriteBoundingBox>> &bb);
    Sprite(const Sprite& sprite);
    virtual ~Sprite() {}

    void set_current_state(const string &name);

    shared_ptr<SpriteState> get_state(const string &name) { return _states[name]; }

    shared_ptr<SpriteState> get_current_state() { return _current_state; }

    shared_ptr<SpriteFrame> get_current_frame()
    {
        return _current_state != nullptr ? _current_state->get_frame(_current_index) : nullptr;
    }

    shared_ptr<SpriteBoundingBox> get_bounding_box() { return _bounding_boxes[BOUNDING_BOX]; }

    const BomberCoordinates &get_coords() const { return _coords; }

    void move(int offset_x, int offset_y);
    void set_position(const BomberCoordinates& coords);

    virtual void init(BomberGraphicsRenderer *renderer);
    virtual bool update(int elapsed_ms);
    virtual void draw(BomberGraphicsRenderer *renderer);

    virtual shared_ptr<Sprite> clone();

    friend ostream &operator<<(std::ostream &os, const Sprite &p);

private:
    int _current_index;
    int _current_elapsed_time;
    map<string, shared_ptr<SpriteState>> _states;
    map<string, shared_ptr<SpriteBoundingBox>> _bounding_boxes;
    shared_ptr<SpriteState> _current_state;
    BomberCoordinates _coords;
};

class SpritesRepository : public DisplayableItemsRepository<Sprite>
{
public:
    SpritesRepository() : DisplayableItemsRepository<Sprite>() {}
    ~SpritesRepository() {}

    virtual void dump();
};