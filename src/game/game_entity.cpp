#include "game_entity.h"
#include "bomber_logger.h"

void Entity::init(BomberGraphicsRenderer *renderer)
{
    _sprite->init(renderer);
    _sprite->set_current_state("idle");
}

bool Entity::has_speed()
{
    return (_velocity.x_offset != 0 || _velocity.y_offset != 0);
}

bool Entity::update(Level* level, int elapsed_ms)
{
    _sprite->update(elapsed_ms);
    if (has_speed())
    {
        return move(level, _velocity.x_offset, _velocity.y_offset);
    }
    return false;
}

bool Entity::move(Level* level, int x_offset, int y_offset)
{

    BomberCoordinates next_coords(
        (double) x_offset + (double)_sprite->get_coords().get_x(),
        (double) y_offset + (double)_sprite->get_coords().get_y());

    BomberCoordinates x1_y1(
        next_coords.get_x() -level->get_dimension().get_cell_width()/2 + _sprite->get_bounding_box()->get_x() + 2,
        next_coords.get_y() -level->get_dimension().get_cell_height()/2 + _sprite->get_bounding_box()->get_y() + 2 );
    BomberCoordinates x2_y1(
        next_coords.get_x() -level->get_dimension().get_cell_width()/2 + _sprite->get_bounding_box()->get_x() + _sprite->get_bounding_box()->get_width() -2, 
        next_coords.get_y() -level->get_dimension().get_cell_height()/2+ _sprite->get_bounding_box()->get_y() + 2);
    BomberCoordinates x2_y2(
        next_coords.get_x() -level->get_dimension().get_cell_width()/2 + _sprite->get_bounding_box()->get_x() + _sprite->get_bounding_box()->get_width() -2, 
        next_coords.get_y() -level->get_dimension().get_cell_height()/2+ _sprite->get_bounding_box()->get_y() + _sprite->get_bounding_box()->get_height() -2);
    BomberCoordinates x1_y2(
        next_coords.get_x()-level->get_dimension().get_cell_width()/2+ _sprite->get_bounding_box()->get_x() + 2, 
        next_coords.get_y() -level->get_dimension().get_cell_height()/2+ _sprite->get_bounding_box()->get_y() + _sprite->get_bounding_box()->get_height() -2) ;

    if (can_move(level, x1_y1) && can_move(level, x2_y1) && can_move(level, x2_y2) && can_move(level, x1_y2)) 
    {
         _sprite->set_position(next_coords);
         return true;
    }
    return false;
}

bool Entity::can_move(Level* level, const BomberCoordinates& coords) {
    auto grid_coords = level->get_grid_coords(coords);
    auto material = level->get_tile_material(grid_coords);
    cout << "(" << grid_coords.get_column() << "," << grid_coords.get_row() << "):" << (int)material << endl;
    return TTile_material::GROUND == material;
}

void Entity::draw(BomberGraphicsRenderer *renderer)
{
    _sprite->draw(renderer);
}

void Entity::set_position(const BomberCoordinates &coords)
{
    BomberLogger::get_instance()->info("SPRITE:SET_POS({})", coords.get_x(), coords.get_y());
    _sprite->set_position(coords);
}

void Entity::set_velocity(int xoffset, int yoffset)
{
    _velocity.x_offset = xoffset;
    _velocity.y_offset = yoffset;
}
