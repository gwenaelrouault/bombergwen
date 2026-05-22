#include "game_assets.h"
#include "bomber_logger.h"

shared_ptr<Sprite> SpriteGameAsset::load()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:SPRITES:sprite:{}:load - START", _name.c_str());
    // parse AseSprite sprite json file
    auto ase_sp_metadata = AseSpritesheet::parse(_filename);
    ase_sp_metadata->dump();
    // load sprite sheet
    auto spritesheet = BomberSpriteSheet::load_from_png(_spritesheet_filename);
    auto parsed_tags = ase_sp_metadata->get_tags();
    auto parsed_frames = ase_sp_metadata->get_frames();
    auto parsed_slices = ase_sp_metadata->get_slices();
    // load states and frames...
    vector<shared_ptr<SpriteState>> states;
    states.reserve(parsed_tags.size());
    for (auto tag = parsed_tags.begin(); tag != parsed_tags.end(); ++tag)
    {
        vector<shared_ptr<SpriteFrame>> frames;
        for (int i = tag->second.get_from(); i <= tag->second.get_to(); i++)
        {
            // association frames with states
            auto frame = parsed_frames.at(i);
            BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:level:{}:load frame({},{})", _name.c_str(), tag->first.c_str(), i);
            auto img = spritesheet->load(frame.get_x(), frame.get_y(), frame.get_width(), frame.get_height());
            auto new_frame = make_shared<SpriteFrame>(
                frame.get_width(), frame.get_height(),
                frame.get_duration(),
                frame.get_x(), frame.get_y(),
                img);
            frames.push_back(new_frame);
        }
        states.push_back(make_shared<SpriteState>(tag->first, tag->second.is_repeated(), frames));
    }
    // load bounding box
    vector<shared_ptr<SpriteBoundingBox>> boundingBoxes;
    boundingBoxes.reserve(parsed_tags.size());
    for (auto slice = parsed_slices.begin(); slice != parsed_slices.end(); ++slice)
    {
        boundingBoxes.push_back(make_shared<SpriteBoundingBox>(slice->get_name(), slice->get_x(), slice->get_y(), slice->get_width(), slice->get_height()));
    }

    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:SPRITES:sprite:{}:load - END", _name.c_str());
    return make_shared<Sprite>(_name, states, boundingBoxes);
}

shared_ptr<Level> LevelGameAsset::load()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:level:{}:load - START", _name.c_str());
    // parse AseSprite level json file
    auto ase_sp_metadata = AseSpritesheet::parse(_filename);
    ase_sp_metadata->dump();
    auto parsed_frames = ase_sp_metadata->get_frames();
    auto parsed_tags = ase_sp_metadata->get_tags();
    map<int, TTile_material> materials;
    // parse map
    auto level_map = LevelGameMap::parse(ase_sp_metadata, _level_map_filename);
    for (auto tag = parsed_tags.begin(); tag != parsed_tags.end(); ++tag)
    {
        int from_frame_index = tag->second.get_from();
        int to_frame_index = tag->second.get_to();
        string material_name = tag->second.get_name();
        TTile_material material = GROUND;
        if (material_name == "plot")
        {
            material = PLOT;
        }
        else if (material_name == "deco")
        {
            material = DECO;
        }
        for (int i = from_frame_index; i <= to_frame_index; i++)
        {
            materials.insert({i, material});
        }
    }
    level_map->dump();
    // parse spritesheet PNG
    vector<shared_ptr<BomberImg>> sp_tiles;
    auto spritesheet = BomberSpriteSheet::load_from_png(_spritesheet_filename);
    for (auto &frame : parsed_frames)
    {
        sp_tiles.push_back(spritesheet->load(frame.get_x(), frame.get_y(), frame.get_width(), frame.get_height()));
    }
    vector<shared_ptr<BomberImg>> tiles;
    map<int, TTile_material> tiles_materials;
    for (int i = 0; i < level_map->get_size(); i++)
    {
        int frame_index = level_map->get_cell(i);
        BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:level:{}:load {}:{}", _name.c_str(), i, frame_index);
        if (frame_index < sp_tiles.size())
        {
            auto tile_img = sp_tiles[frame_index];
            tiles.push_back(tile_img);
            tiles_materials.insert({i, GROUND});
        }
        else
        {
            stringstream ss;
            ss << "Invalid tile(" << i << "):" << frame_index << "(map size=" << sp_tiles.size() << ")";
            throw InvalidAssetException(ss.str());
        }
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:ASSET:level:{}:load - END", _name.c_str());
    return make_shared<Level>(level_map->get_name(), 32, 32, level_map->get_columns(), level_map->get_rows(), level_map->get_default_camera(), tiles_materials, tiles);
}

tuple<shared_ptr<SpritesRepository>, shared_ptr<LevelsRepository>> GameAssets::load()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:load - START");
    auto sprites = load_sprites();
    auto levels = load_levels();
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:load - END");
    return make_tuple(sprites, levels);
}

shared_ptr<SpritesRepository> GameAssets::load_sprites()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:SPRITES:load - START");
    auto sprites = make_shared<SpritesRepository>();
    map<string, shared_ptr<SpriteGameAsset>> sprite_assets;
    for (auto it = _configuration_sprites.begin(); it != _configuration_sprites.end(); ++it)
    {
        sprite_assets[it->first] = make_shared<SpriteGameAsset>(it->first, ::get<0>(it->second), ::get<1>(it->second));
    }
    for (auto it = sprite_assets.begin(); it != sprite_assets.end(); ++it)
    {
        auto sprite = it->second->load();
        sprites->add(sprite->get_name(), sprite);
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:SPRITES:load - END");
    return sprites;
}

shared_ptr<LevelsRepository> GameAssets::load_levels()
{
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:LEVELS:load - START");
    auto levels = make_shared<LevelsRepository>();
    map<string, shared_ptr<LevelGameAsset>> level_assets;
    for (auto it = _configuration_levels.begin(); it != _configuration_levels.end(); ++it)
    {
        level_assets[it->first] = make_shared<LevelGameAsset>(it->first, ::get<0>(it->second), ::get<1>(it->second), ::get<2>(it->second));
    }
    for (auto it = level_assets.begin(); it != level_assets.end(); ++it)
    {
        auto level = it->second->load();
        levels->add(level->get_name(), level);
    }
    BomberLogger::get_instance()->info("GAME:ENGINE:ASSETS:LEVELS:load - END");
    return levels;
}