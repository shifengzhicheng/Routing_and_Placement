#include "Astar.h"
#include "Point.h"

Astar::Astar(std::vector<std::vector<int>> &_maze)
{
    this->maze = _maze;
}

// 计算路径返回指针列表
std::list<std::shared_ptr<Point>> Astar::GetPath(Point startPoint, Point endPoint)
{

    std::shared_ptr<Point> result = findPath(startPoint, endPoint);
    std::list<std::shared_ptr<Point>> path;
    // 返回路径，如果没找到路径则返回空链表
    while (result)
    {
        path.push_front(result);
        result = result->parent;
    }

    return path;
}

// A*算法
std::shared_ptr<Point> Astar::findPath(Point startPoint, Point endPoint)
{
    // 先清空openlist和closelist
    openList.clear();
    closeList.clear();

    std::shared_ptr<Point> newEndPoint(new Point(endPoint.x, endPoint.y));
    openList.push_back(std::shared_ptr<Point>(new Point(startPoint.x, startPoint.y)));

    while (!openList.empty())
    {
        auto curPoint = getLeastGpoint();
        openList.remove(curPoint);
        closeList.push_back(curPoint);
        // 1，找到当前周围的四个格子中可以通过的格子
        auto surroundPoints = getSurroundPoints(curPoint);
        for (auto &target : surroundPoints)
        {
            // 2，对于某个格子如果不在列表中就加入到开启列表，设置当前格子为其父节点，计算G
            if (!isInList(openList, target))
            {
                target->parent = curPoint;
                target->G = calcG(curPoint, target);
                openList.push_back(target);
            }
            // 对于某个格子，它在开启列表中就计算G值，比原来的大就什么都不做，否则设置它的父节点为当前节点并更新GF
            else
            {
                int tempG = calcG(curPoint, target);
                if (tempG < target->G)
                {
                    target->parent = curPoint;

                    target->G = tempG;
                }
            }
            // 如果找到了目标节点就直接返回
            std::shared_ptr<Point> resPoint = isInList(openList, newEndPoint);
            if (resPoint)
                // 返回指针节点
                return resPoint;
        }
    }
    // 失败返回NULL
    return NULL;
}

std::list<std::shared_ptr<Point>> Astar::getSearchPath()
{
    return closeList;
}

/*  找到G值最小的下一个节点 */
std::shared_ptr<Point> Astar::getLeastGpoint()
{
    if (!openList.empty())
    {
        auto resPoint = openList.front();
        for (auto &point : openList)
        {
            if (point->G < resPoint->G)
            {
                resPoint = point;
            }
        }
        return resPoint;
    }
    return NULL;
}

std::vector<std::shared_ptr<Point>> Astar::getSurroundPoints(std::shared_ptr<Point> point) const
{
    std::vector<std::shared_ptr<Point>> surroundPoints;
    std::vector<std::pair<int, int>> coordinates = {
        {point->x - 1, point->y},
        {point->x, point->y - 1},
        {point->x + 1, point->y},
        {point->x, point->y + 1}};

    for (const auto &coord : coordinates)
    {
        std::shared_ptr<Point> newPoint = std::make_shared<Point>(coord.first, coord.second);
        if (isCanReach(point, newPoint))
            surroundPoints.push_back(newPoint);
    }

    return surroundPoints;
}

// 判断是否可以通过
bool Astar::isCanReach(std::shared_ptr<Point> point, std::shared_ptr<Point> target) const
{
    // 如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
    if (
        (target->x < 0 || target->x >= maze[0].size()) ||
        (target->y < 0 || target->y >= maze.size()) ||
        (maze[target->y][target->x] == 1) ||
        (isInList(closeList, target)))
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::shared_ptr<Point> Astar::isInList(std::list<std::shared_ptr<Point>> list, std::shared_ptr<Point> point) const
{
    // 判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for (auto p : list)
        if (p->x == point->x && p->y == point->y)
            return p;
    return NULL;
}

/* 曼哈顿距离计算G */
int Astar::calcG(std::shared_ptr<Point> temp_point, std::shared_ptr<Point> point)
{
    int extraG = abs(point->x - temp_point->x) + abs(point->y - temp_point->y);
    int parentG = point->parent == NULL ? 0 : point->parent->G;
    return extraG + parentG;
}

Point Astar::findone(std::shared_ptr<Point> point, Point end)
{
    openList.clear();
    closeList.clear();
    std::shared_ptr<Point> newend(new Point(end));
    auto surroundingpoints = getSurroundPoints(point);
    for (auto &target : surroundingpoints)
    {
        target->G = calcG(point, target);
    }
    Point temp;
    for (auto &target : surroundingpoints)
    {
        if (target->G < temp.G)
        {
            temp = *target;
        }
    }
    return temp;
}