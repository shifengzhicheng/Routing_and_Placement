#pragma once
#include "parser.h"
#include "FM_Algorithm.h"
#include "Astar.h";
class Routing
{
public:
    // 完成解析输出的类型
    int type;
    std::string filename;
    // 构造Routing类
    Routing(parser& p)
    {
        Maze = p.getMaze();
        modules = p.getModules();
        filename = p.getFileName();
        type = p.type;
    };
    // FM算法
    void performFM();
    // Astar算法
    void performAstar();
    // 输出文件
    void outputfile();
    //计算布线代价
    int cost_of_routing_Astar();//Astar
    int cost_of_FM();           //FM
private:
    void connect(std::vector<std::vector<int>>& Maze, int source, int target, std::vector<int> &parent);
    // 矩阵
    std::vector<std::vector<int>> Maze;
    // 模块连接关系
    std::vector<std::vector<int>> modules;
    // 划分
    std::vector<std::vector<int>> partition;
    // Astar代理
    AStarGraph Astar;
    // FM算法实现代理
    FM fm;
};
