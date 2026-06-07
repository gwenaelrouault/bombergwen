#pragma once

#include <tuple>
#include <string>
#include <map>
#include <memory>

#include "bomber_graphics.h"
#include "ase_parser.h"
#include "map_parser.h"
#include "sprites.h"
#include "levels.h"
#include "bomber_object.h"
#include "bomber_exceptions.h"

using namespace std;

typedef enum
{
    LEVEL,
    SPRITE
} AssetType;

class InvalidAssetException : public BomberException
{
public:
    InvalidAssetException(const std::string &msg) : BomberException(msg) {}
};

template <typename T>
class GameAsset
{
public:
    GameAsset(const string &name, const string &filename, const string &spritesheet_filename)
        : _name(name), _filename(filename), _spritesheet_filename(spritesheet_filename) {}
    virtual ~GameAsset() {}

    virtual shared_ptr<T> load() = 0;

protected:
    string _name;
    string _filename;
    string _spritesheet_filename;
};

class SpriteGameAsset : public GameAsset<Sprite>
{
public:
    SpriteGameAsset(const string &name, const string &filename, const string &spritesheet_filename)
        : GameAsset<Sprite>(name, filename, spritesheet_filename) {}
    virtual ~SpriteGameAsset() {}

    virtual shared_ptr<Sprite> load();

private:
};


class LevelGameAsset : public GameAsset<Level>
{
public:
    LevelGameAsset(const string &name, const string &filename, const string &spritesheet_filename, const string& level_map_filename)
        : _level_map_filename(level_map_filename), GameAsset<Level>(name, filename, spritesheet_filename) {}
    virtual ~LevelGameAsset() {}

    virtual shared_ptr<Level> load();

private:
    string _level_map_filename;
};

class GameAssets
{
public:
    GameAssets()
    {
        _configuration_sprites[NAME_HERO] = tuple<string, string>("../resources/bomb.json", "../resources/bomb.png");
        _configuration_levels[NAME_LEVEL_1] = tuple<string, string, string>(
            "../resources/bomber_tiles.json", 
            "../resources/bomber_tiles.png", 
            "../resources/level1.json");
        _configuration_objects[BOMB1] =  tuple<string, string>("../resources/bomb1.json", "../resources/bomb1.png");
        _configuration_objects[BOMB2] =  tuple<string, string>("../resources/bomb2.json", "../resources/bomb2.png");
    }
    ~GameAssets() {}

    tuple<shared_ptr<SpritesRepository>, shared_ptr<LevelsRepository>, shared_ptr<ObjectRepository>> load();

private:
    map<string, tuple<string, string>> _configuration_sprites;
    map<string, tuple<string, string, string>> _configuration_levels;
    map<string, tuple<string, string>> _configuration_objects;
    
    shared_ptr<SpritesRepository> load_sprites();
    shared_ptr<LevelsRepository> load_levels();
    shared_ptr<ObjectRepository> load_objects();

};