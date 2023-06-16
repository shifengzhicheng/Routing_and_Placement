#pragma once
#include <vector>
#include <fstream> // 包含文件流头文件
#include <string>  // 包含字符串头文件

struct Point;

enum Operation
{
    OPFM,
    OPAstar
};
class parser
{
public:
    int type;
    parser(std::string, std::string);
    int parse();
    std::string returninfo();
    std::vector<std::vector<int>>& getMaze();
    std::vector<std::vector<int>>& getModules();
private:
    std::string filename;
    std::string erroinfo;
    std::vector<std::vector<int>> Maze;
    std::vector<std::vector<int>> Modules;
};