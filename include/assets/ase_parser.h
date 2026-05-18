#pragma once
#include <iostream>
#include "bomber_exceptions.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class AseParseException : public BomberException
{
public:
    AseParseException(const std::string &msg) : BomberException(msg) {}
};

class AseFrame
{
public:
    AseFrame(const string &name, int x, int y, int w, int h, int duration)
        : _name(name), _x(x), _y(y), _width(w), _height(h), _duration(duration) {}
    ~AseFrame() {}

    const string &get_name() { return _name; }
    int get_x() { return _x; }
    int get_y() { return _y; }
    int get_width() { return _width; }
    int get_height() { return _height; }
    int get_duration() { return _duration; }

    friend ostream &operator<<(std::ostream &os, const AseFrame &f);

private:
    string _name;
    int _x;
    int _y;
    int _width;
    int _height;
    int _duration;
};

class AseTag
{
public:
    AseTag(const string &name, int from_index, int to_index, bool repeated_frame)
        : _name(name), _from(from_index), _to(to_index), _repeated(repeated_frame) {}
    ~AseTag() {}

    const string &get_name() { return _name; }
    int get_from() { return _from; }
    int get_to() { return _to; }
    bool is_repeated() { return _repeated; }

    friend ostream &operator<<(std::ostream &os, const AseTag &p);

private:
    string _name;
    int _from;
    int _to;
    bool _repeated;
};

class AseSpritesheet
{
public:
    AseSpritesheet(int width, int height) : _width(width), _height(height) {}
    ~AseSpritesheet() {}
    const map<string, AseTag> &get_tags() { return _tags; }
    const vector<AseFrame> &get_frames() { return _frames; }

    void add_tag(const string &name, int from_index, int to_index, bool repeated_frame);
    void add_frame(const string &name, int x, int y, int width, int height, int duration);

    friend ostream &operator<<(std::ostream &os, const AseSpritesheet &p);

    void dump();

    static shared_ptr<AseSpritesheet> parse(const string &filename);

private:
    int _width;
    int _height;
    map<string, AseTag> _tags;
    vector<AseFrame> _frames;

    int extract_number_from_name(const string &name);
};
