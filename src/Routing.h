#pragma once
#include "parser.h"
#include "FM.h"
#include "Astar.h";
class Routing
{
public:
    // 完成解析输出的类型
    int type;
    std::string filename;
    // 构造Routing类
    Routing(parser& p) {
        Maze = p.getMaze();
        modules = p.getModules();
        type = p.type;
    };
    // FM算法
    void performFM();
    // Astar算法
    void performAstar();
    // 输出文件
    void outputfile();

private:
    // 矩阵
    std::vector<std::vector<int>> Maze;
    // 模块连接关系
    std::vector<std::vector<int>> modules;
    // Astar代理
    AStarGraph Astar;
    // FM代理
    FM fm;
};