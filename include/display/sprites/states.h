#pragma once

#include "frames.h"
#include "assets_def.h"
#include <vector>

class SpriteState
{
public:

    SpriteState(const SpriteState& state);

    SpriteState(const string &name, bool is_repeated, vector<shared_ptr<SpriteFrame>> &frames);
    ~SpriteState() {}

    void init(BomberGraphicsRenderer *renderer);

    const string &get_name() { return _name; }

    shared_ptr<SpriteFrame> get_frame(int frame_number) { return _frames.at(frame_number); }

    shared_ptr<SpriteState> clone();

    bool is_repeated() { return _is_repeated; }

    size_t get_frames_nb() { return _frames.size(); }

    friend ostream &operator<<(std::ostream &os, const SpriteState &p);

private:
    string _name;
    bool _is_repeated;
    vector<shared_ptr<SpriteFrame>> _frames;
};