#include "states.h"

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

SpriteState::SpriteState(const string &name, bool is_repeated, vector<shared_ptr<SpriteFrame>> &frames)
    : _name(name), _is_repeated(is_repeated)
{
    for (auto frame : frames)
    {
        _frames.push_back(frame);
    }
}

SpriteState::SpriteState(const SpriteState &state)
{
    _name = state._name;
    _is_repeated = state._is_repeated;
    for (auto frame : state._frames)
    {
        _frames.push_back(frame);
    }
}

void SpriteState::init(BomberGraphicsRenderer *renderer)
{
    for (auto frame : _frames)
    {
        frame->load_texture(renderer);
    }
}

shared_ptr<SpriteState> SpriteState::clone()
{
    return make_shared<SpriteState>(*this);
}