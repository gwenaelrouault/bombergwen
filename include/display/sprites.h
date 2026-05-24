#pragma once

#include <vector>
#include <iostream>
#include "display_items.h"
#include "assets_def.h"

class SpriteBoundingBox
{
public:
    SpriteBoundingBox(const string& name, int x, int y, int w, int h)
        : _name(name), _x(x), _y(y), _width(w), _height(h) {}
    ~SpriteBoundingBox() {}

    const string& get_name() const { return _name; }
    int get_x() const { return _x; }
    int get_y() const { return _y; }
    int get_width() const { return _width; }
    int get_height() const { return _height; }

private:
    string _name;
    int _x;
    int _y;
    int _width;
    int _height;
};

class SpriteFrame
{
public:
    SpriteFrame(int width, int height, int duration, int src_x, int src_y, shared_ptr<BomberImg> img)
        : _width(width), _height(height), _duration(duration), _src_x(src_x), _src_y(src_y), _img(img), _texture(nullptr) {}
    ~SpriteFrame() {}

    int get_width() { return _width; }
    int get_height() { return _height; }
    int get_duration() { return _duration; }

    shared_ptr<BomberImg> get_img() { return _img; }
    shared_ptr<BomberTexture> get_texture() { return _texture; }

    void load_texture(BomberGraphicsRenderer *renderer);

    friend ostream &operator<<(std::ostream &os, const SpriteFrame &p);

private:
    int _width;
    int _height;
    int _duration;
    int _src_x;
    int _src_y;
    shared_ptr<BomberImg> _img;
    shared_ptr<BomberTexture> _texture;
};

class SpriteState
{
public:
    SpriteState(const string &name, bool is_repeated, vector<shared_ptr<SpriteFrame>> &frames)
        : _name(name), _is_repeated(is_repeated)
    {
        for (auto &frame : frames)
        {
            _frames.push_back(frame);
        }
    }
    ~SpriteState() {}

    void init(BomberGraphicsRenderer *renderer);

    const string &get_name() { return _name; }

    friend ostream &operator<<(std::ostream &os, const SpriteState &p);

    shared_ptr<SpriteFrame> get_frame(int frame_number) { return _frames.at(frame_number); }

    bool is_repeated() { return _is_repeated; }

    size_t get_frames_nb() { return _frames.size(); }

private:
    string _name;
    bool _is_repeated;
    vector<shared_ptr<SpriteFrame>> _frames;
};

class Sprite : public DisplayableItem
{
public:
    Sprite(const string &name, vector<shared_ptr<SpriteState>> &states, vector<shared_ptr<SpriteBoundingBox>> &bb)
        : DisplayableItem(name), _current_index(0), _current_elapsed_time(0)
    {
        for (auto &state : states)
        {
            _states.insert({state->get_name(), state});
        }
        for (auto &bbox : bb)
        {
            _bounding_boxes.insert({bbox->get_name(), bbox});
        }
    }
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