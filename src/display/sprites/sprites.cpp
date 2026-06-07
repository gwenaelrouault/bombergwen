#include "sprites.h"
#include "bomber_logger.h"


ostream &operator<<(std::ostream &os, const Sprite &s)
{
    os << "Sprite(" << s._name << ")" << endl;
    int i = 0;
    for (auto &state_it : s._states)
    {
        auto state = state_it.second;
        os << *state.get();
    }
    return os;
}

SpriteBoundingBox::SpriteBoundingBox(const SpriteBoundingBox& box)
{
    _name = box._name;
    _x = box._x;
    _y = box._y;
    _width = box._width;
    _height = box._height;
}

shared_ptr<SpriteBoundingBox> SpriteBoundingBox::clone()
{
    return make_shared<SpriteBoundingBox>(*this);
}

Sprite::Sprite(const string &name, vector<shared_ptr<SpriteState>> &states, vector<shared_ptr<SpriteBoundingBox>> &bb)
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

Sprite::Sprite(const Sprite &sprite) : DisplayableItem(sprite)
{
    _current_index = sprite._current_index;
    _current_elapsed_time = sprite._current_elapsed_time;
    _coords = sprite._coords;
    for (auto it =  sprite._states.begin(); it !=  sprite._states.end(); it++)
    {
        _states.insert({it->first, it->second->clone()});
    }
    for (auto it = sprite._bounding_boxes.begin(); it != sprite._bounding_boxes.end(); it++)
    {
        _bounding_boxes.insert({it->first, it->second->clone()});
    }
    if (sprite._current_state == nullptr)
    {
        _current_state = nullptr;
    }
    else
    {
        _current_state = _states[sprite._current_state->get_name()];
    }
}

void Sprite::init(BomberGraphicsRenderer *renderer)
{
    for (auto state_it = _states.begin(); state_it != _states.end(); state_it++)
    {
        auto state = state_it->second;
        state->init(renderer);
    }
}

void Sprite::move(int offset_x, int offset_y)
{
    _coords.set_x(_coords.get_x() + (double)offset_x);
    _coords.set_y(_coords.get_y() + (double)offset_y);
}

void Sprite::set_position(const BomberCoordinates &coords)
{
    _coords = coords;
}

bool Sprite::update(int elapsed_ms)
{
    bool frame_update = false;
    _current_elapsed_time += elapsed_ms;
    auto current_frame = get_current_frame();
    if (current_frame != nullptr && _current_elapsed_time >= current_frame->get_duration())
    {
        int next_index = _current_index + 1;
        if (next_index < (int)_current_state->get_frames_nb())
        {
            _current_index = next_index;
            frame_update = true;
        }
        else if (_current_state->is_repeated())
        {
            _current_index = 0;
            frame_update = true;
        }
        _current_elapsed_time = 0;
    }
    return frame_update;
}

void Sprite::draw(BomberGraphicsRenderer *renderer)
{
    if (get_current_frame() != nullptr)
    {
        renderer->draw(get_current_frame()->get_texture().get(), _coords);
    }
}

void Sprite::set_current_state(const string &name)
{
    shared_ptr<SpriteState> new_state = get_state(name);
    if (new_state != nullptr)
    {
        if (_current_state == nullptr || new_state->get_name() != _current_state->get_name())
        {
            string current_name = _current_state == nullptr ? "" : _current_state->get_name();
            BomberLogger::get_instance()->info("SPRITE:change state {}->{}", current_name.c_str(), new_state->get_name().c_str());
            _current_state = new_state;
            _current_index = 0;
            _current_elapsed_time = 0;
        }
    }
    else
    {
        BomberLogger::get_instance()->error("SPRITE:cannot set state {}", name);
    }
}

shared_ptr<Sprite> Sprite::clone()
{
    return make_shared<Sprite>(*this);
}

void SpritesRepository::dump()
{
    cout << "loaded sprites=" << _items.size() << endl;
    for (auto &sprite_it : _items)
    {
        auto sprite = sprite_it.second;
        cout << *sprite.get() << endl;
    }
}
