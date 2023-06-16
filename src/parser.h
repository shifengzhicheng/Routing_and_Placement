#pragma once
#include <vector>
#include <fstream> // 包含文件流头文件
#include <string>  // 包含字符串头文件
enum Operation
{
    FM,
    Astar
};
class parser
{
public:
    std::vector<std::vector> &getMaze();
    std::vector<std::vector> &getModules();

private:
};