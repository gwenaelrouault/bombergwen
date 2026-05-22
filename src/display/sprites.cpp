#include "sprites.h"
#include <syslog.h>

ostream &operator<<(std::ostream &os, const SpriteFrame &f)
{
    os << "Frame(width:" << f._width << ",height:" << f._height << ",sp:" << f._src_x << "," << f._src_y << ")";
    return os;
}

ostream &operator<<(std::ostream &os, const SpriteState &s)
{
    os << "\tState(" << s._name << ",repeat=" << s._is_repeated << ")" << endl;
    int i = 0;
    for (auto &frame : s._frames)
    {
        os << "\t\t" << i++ << ":" << *frame.get() << endl;
    }
    return os;
}

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

void SpriteFrame::load_texture(BomberGraphicsRenderer *renderer)
{
    _texture = renderer->load_texture(_img.get());
}

void SpriteState::init(BomberGraphicsRenderer *renderer)
{
    for (auto &frame : _frames)
    {
        frame->load_texture(renderer);
    }
}

void Sprite::init(BomberGraphicsRenderer *renderer)
{
    for (auto state_it = _states.begin(); state_it != _states.end(); ++state_it)
    {
        auto state = state_it->second;
        state->init(renderer);
    }
}

void Sprite::move(int offset_x, int offset_y)
{
    _coords.set_x(_coords.get_x() + (double) offset_x);
    _coords.set_y(_coords.get_y() + (double) offset_y);
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
            syslog(LOG_INFO, "SPRITE:change state %s->%s", current_name.c_str(), new_state->get_name().c_str());
            _current_state = new_state;
            _current_index = 0;
            _current_elapsed_time = 0;
            //_box.w = _current_state->get_frame(0)->get_width() * 2;
            //_box.h = _current_state->get_frame(0)->get_height() *2 ;
            // cout << "->change state " << _current_state->get_name()
            //    << ":" <<  current_name
            //   << ",box=[" <<  _box.w << "," << _box.h << "," << _box.x << "," << _box.y << "]"
            // << endl;
        }
    }
    else
    {
        syslog(LOG_INFO, "SPRITE:ERROR STATE");
    }
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
