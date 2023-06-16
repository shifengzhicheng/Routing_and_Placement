#pragma once
#include <memory>

struct Point
{
    int x, y;
    int G;
    std::shared_ptr<Point> parent;
    std::shared_ptr<Point> next;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
        G = 0;
        parent = NULL;
        next = NULL;
    }
    Point()
    {
        x = y = G = 0;
        parent = next = NULL;
    }
};