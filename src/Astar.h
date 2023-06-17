#pragma once
#include <vector>
#include <limits>
#include <cmath>
struct Edge
{              // 表示边
    int sid_;  // 边的起始节点
    int eid_;  // 边的结束节点
    double w_; // 边的权重
    Edge() = default;
    Edge(int s, int e, double w)
        : sid_(s), eid_(e), w_(w) {}
};
struct Vertex
{
    int id_;
    double dist_; // 算法实现中，记录第一个节点到这个节点的距离
    double f_;    // f(i)=g(i)+h(i)
    int x_, y_;   // 顶点在地图中的坐标（x, y）
    Vertex() = default;
    Vertex(int id, int x, int y)
        : id_(id), x_(x), y_(y), dist_(std::numeric_limits<double>::max()), f_(std::numeric_limits<double>::max()) {}
};

class AStarGraph
{
public:
    AStarGraph(){};
    void CreateGraph(std::vector<std::vector<int>> &_Maze); // 创建图
    void addEdge(int s, int e, double w);                   // 添加边
    void addVertex(int id, int x, int y);                   // 添加节点
    std::vector<int> AStar(int s, int e);                   // 寻路
    void Initial();                                         // 初始化
    std::vector<int> &getConnectionPoint()                  // 返回需要连接的点的关系
    {
        return ConnectionPoint;
    };
    void modifyWeight(int s,int t,double w);// 改变边的权重
    void drawGrid(const std::vector<std::vector<int>>& maze);
private:
    const int TILE_SIZE = 20;  // 方格的大小
    std::vector<std::vector<Edge>> adj_; // 邻接表
    int v_count_;                        // 顶点数
    std::vector<Vertex> vertexes;        // 记录所有顶点，主要记录坐标
    double hManhattan(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
    std::vector<int> ConnectionPoint;
};
