#pragma once
#include<vector>
#include<limits>
#include<cmath>
struct Edge { // 表示边
    int sid_; // 边的起始节点
    int eid_; // 边的结束节点
    double w_;   // 边的权重
    Edge() = default;
    Edge(int s, int e, double w)
        : sid_(s), eid_(e), w_(w) {}
};
struct Vertex { // 算法实现中，记录第一个节点到这个节点的距离
    int id_;
    double dist_;
    double f_;      // f(i)=g(i)+h(i)
    int x_, y_;   // 顶点在地图中的坐标（x, y）
    Vertex() = default;
    Vertex(int id, int x, int y)
        : id_(id), x_(x), y_(y)
        , dist_(std::numeric_limits<double>::max())
        , f_(std::numeric_limits<double>::max()) {}
};

class AStarGraph {
public:
    AStarGraph() {};
    void CreateGraph(std::vector<std::vector<int>>& _Maze);
    void addEdge(int s, int e, double w);
    void addVertex(int id, int x, int y);
    std::vector<int> AStar(int s, int e);
    void Initial();
    std::vector<int> &getConnectionPoint() {
        return ConnectionPoint;
    };
private:
    std::vector<std::vector<Edge>> adj_;    // 邻接表
    int v_count_;                           // 顶点数
    std::vector<Vertex> vertexes;           // 记录所有顶点，主要记录坐标
    double hManhattan(int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
    std::vector<int> ConnectionPoint;
};

