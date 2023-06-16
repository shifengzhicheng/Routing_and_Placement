#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include "Point.h"

class Astar
{
private:
    std::vector<std::vector<int>> maze;
    std::list<std::shared_ptr<Point>> openList;
    std::list<std::shared_ptr<Point>> closeList;
    std::shared_ptr<Point> findPath(Point startPoint, Point endPoint);
    std::shared_ptr<Point> isInList(std::list<std::shared_ptr<Point>> list, std::shared_ptr<Point> point) const;

public:
    Astar(){};
    Astar(std::vector<std::vector<int>> &_maze);
    std::list<std::shared_ptr<Point>> GetPath(Point startPoint, Point endPoint);
    std::list<std::shared_ptr<Point>> getSearchPath();
    std::vector<std::shared_ptr<Point>> getSurroundPoints(std::shared_ptr<Point> point) const;
    std::shared_ptr<Point> getLeastGpoint();
    bool isCanReach(std::shared_ptr<Point> point, std::shared_ptr<Point> target) const;
    int calcG(std::shared_ptr<Point> temp_start, std::shared_ptr<Point> point);
    Point findone(std::shared_ptr<Point> point, Point end);
};
