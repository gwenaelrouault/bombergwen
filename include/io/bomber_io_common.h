#pragma once

typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
} BomberRect;

class BomberCoordinates
{
public:
    BomberCoordinates() : _x(0), _y(0) {}

    BomberCoordinates(int x, int y) : _x(x), _y(y) {}

    BomberCoordinates(const BomberCoordinates &coords)
        : _x(coords.get_x()), _y(coords.get_y()) {}

    ~BomberCoordinates() {}

    int get_x() const { return _x; }

    int get_y() const { return _y; }

    void set_x(int x) { _x = x; }
    void set_y(int y) { _y = y; }

private:
    int _x;
    int _y;
};

class BomberDimensions
{
public:
    BomberDimensions() : _width(0), _height(0) {}

    BomberDimensions(int width, int height) : _width(width), _height(height) {}

    BomberDimensions(const BomberDimensions &dim) : _width(dim.get_width()), _height(dim.get_height()) {}

    ~BomberDimensions() {}

    int get_width() const { return _width; }

    int get_height() const { return _height; }

    void set_width(int width) { _width = width; }
    void set_height(int height) { _height = height; }

private:
    int _width;
    int _height;
};