#pragma once
#include <vector>
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