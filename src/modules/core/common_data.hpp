
#ifndef COMMON_DATA_HPP
#define COMMON_DATA_HPP

#include <cstdint>

class Point
{
public:
    int x, y;

public:
    Point(int x = 0, int y = 0)
            : x(x), y(y) {}
};

class Size
{
public:
    int width, height;

public:
    Size(int width = 0, int height = 0)
            : width(width), height(height) {}

    bool operator==(const Size& other)
    {
        return (width == other.width) && (height == other.height);
    }

    bool operator!=(const Size& other)
    {
        return !(*this == other);
    }
};


class Rect
{
public:
    int x, y, width, height;

public:
    Rect(int x = 0, int y = 0, int width = 0, int height = 0)
            : x(x), y(y), width(width), height(height) {}

public:
    Size inline size() const
    {
        return Size(width, height);
    }
};
#endif //COMMON_DATA_HPP