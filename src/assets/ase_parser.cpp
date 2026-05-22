#include "ase_parser.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <regex>
#include "bomber_logger.h"

ostream &operator<<(std::ostream &os, const AseFrame &f)
{
    os << "Frame(name:" << f._name
       << ",x:" << f._x << ",y:" << f._y
       << ",w:" << f._width << ",h:" << f._height
       << ",duration:" << f._duration << ")";
    return os;
}

ostream &operator<<(std::ostream &os, const AseTag &tag)
{
    os << "Tag(name:" << tag._name
       << ",from:" << tag._from << ",to:" << tag._to
       << ",repeated:" << tag._repeated << ")";
    return os;
}

ostream &operator<<(std::ostream &os, const AseSpritesheet &sp)
{
    os << "Spritesheet(" << sp._width << "," << sp._height << ")" << endl;
    for (auto it_tag = sp._tags.begin(); it_tag != sp._tags.end(); ++it_tag)
    {
        AseTag tag = it_tag->second;
        os << "\t" << tag << endl;
    }
    for (auto &frame : sp._frames)
    {
        os << "\t" << frame << endl;
    }
    return os;
}

void AseSpritesheet::add_frame(const string &name, int x, int y, int width, int height, int duration)
{
    vector<AseFrame>::iterator where_insert = _frames.end();
    bool found = false;
    int index = 0;
    int to_insert_index = extract_number_from_name(name);
    for (auto it = _frames.begin(); it != _frames.end() && !found; ++it)
    {
        if (index++ >= to_insert_index)
        {
            where_insert = it;
            found = true;
        }
    }
    _frames.insert(where_insert, AseFrame(name, x, y, width, height, duration));
}

void AseSpritesheet::add_tag(const string &name, int from_index, int to_index, bool repeated_frame)
{
    _tags.insert({name, AseTag(name, from_index, to_index, repeated_frame)});
}

void AseSpritesheet::add_slice(const string &name, int x, int y, int width, int height)
{
    _slices.push_back(AseSlice(name, x, y, width, height));
}

void AseSpritesheet::dump()
{
    cout << *this << endl;
}

int AseSpritesheet::extract_number_from_name(const string &name)
{
    regex exp(R"((\d+)\.ase$)");
    smatch match;

    if (regex_search(name, match, exp))
    {
        return stoi(match[1]);
    }
    return 0;
}

shared_ptr<AseSpritesheet> AseSpritesheet::parse(const string &filename)
{
    try
    {
        BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:AseSpritesheet:parse({}) - START", filename);
        std::ifstream json_file(filename);
        auto parsed_json = nlohmann::json::parse(json_file);
        nlohmann::json json_meta = parsed_json.at("meta");
        int sp_width = json_meta.at("size").at("w");
        int sp_height = json_meta.at("size").at("h");
        auto result = make_shared<AseSpritesheet>(sp_width, sp_height);
        BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:AseSpritesheet:parse({}):width={},height={}", filename, sp_width, sp_height);
        cout << "PARSE frames"<< filename << endl;
        nlohmann::json json_frames = parsed_json.at("frames");
        for (auto it = json_frames.items().begin(); it != json_frames.items().end(); ++it)
        {
            std::string key = it.key();
            auto &value = it.value();
            int x = value.at("frame").at("x");
            int y = value.at("frame").at("y");
            int w = value.at("frame").at("w");
            int h = value.at("frame").at("h");
            int d = value.at("duration");
            BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:AseSpritesheet:parse({}):Frame(x={},y={},w={},h={},d={})", 
                filename, x, y, w, h, d);
            result->add_frame(key, x, y, w, h, d);
            cout << "Frame:" << x << "," << y << endl;
        }
        cout << "PARSE tags"<< filename << endl;
        nlohmann::json json_tags = json_meta.at("frameTags");
        for (auto &tag : json_tags)
        {
            string name = tag.at("name");
            int from_index = tag.at("from");
            int to_index = tag.at("to");
            bool is_repeated = !tag.contains("repeat");
            result->add_tag(name, from_index, to_index, is_repeated);
        }

        nlohmann::json json_slices = json_meta.at("slices");
        for (auto &slices : json_slices)
        {
            string name = slices.at("name");
            nlohmann::json slice_keys = slices.at("keys");
            for (auto &slice_key : slice_keys) {
                nlohmann::json slice_bounds = slice_key.at("bounds");
                int x = slice_bounds.at("x");
                int y = slice_bounds.at("y");
                int w = slice_bounds.at("w");
                int h = slice_bounds.at("h");
                cout << "Slice(" << x << "," << y << "," << w << "," << h << ")" << endl;
                result->add_slice(name, x, y, w, h);
            }
        }

        BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:AseSpritesheet:parse({}) - END", filename);
        return result;
    }
    catch (exception &e)
    {
        string msg_exception = "error:" + filename + e.what();
        throw AseParseException(msg_exception);
    }
}
