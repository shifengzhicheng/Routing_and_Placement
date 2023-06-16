#include"parser.h"
#include"FM.h"
#include"Astar.h;
class Routing{
    public:
    // 完成解析输出的类型
    int type;
    // 构造Routing类
    int Routing(parser &p);
    // FM算法
    void performFM();
    // Astar算法
    void performAstar();
    // 输出文件
    void ouputfile();
    private:
    std::vector<std::vector<int>> Maze;
    std::vector<std::vector<int>> modules;
    Astar myAstar;
    FM myFM;
};