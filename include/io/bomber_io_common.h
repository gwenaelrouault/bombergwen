#pragma once

typedef struct
{
    double x1;
    double y1;
    double x2;
    double y2;
} BomberRect;

class BomberCoordinates
{
public:
    BomberCoordinates() : _x(0.), _y(0.) {}

    BomberCoordinates(double x, double y) : _x(x), _y(y) {}

    BomberCoordinates(const BomberCoordinates &coords)
        : _x(coords.get_x()), _y(coords.get_y()) {}

    ~BomberCoordinates() {}

    double get_x() const { return _x; }

    double get_y() const { return _y; }

    void set_x(double x) { _x = x; }
    void set_y(double y) { _y = y; }

private:
    double _x;
    double _y;
};

class BomberDimensions
{
public:
    BomberDimensions() : _width(0), _height(0) {}

    BomberDimensions(double width, double height) : _width(width), _height(height) {}

    BomberDimensions(const BomberDimensions &dim) : _width(dim.get_width()), _height(dim.get_height()) {}

    ~BomberDimensions() {}

    double get_width() const { return _width; }

    double get_height() const { return _height; }

    void set_width(double width) { _width = width; }
    void set_height(double height) { _height = height; }

private:
    double _width;
    double _height;
};