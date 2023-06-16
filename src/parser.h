#pragma once
#include <vector>
#include <fstream> // 包含文件流头文件
#include <string>  // 包含字符串头文件
enum Operation
{
    OPFM,
    OPAstar
};
class parser
{
public:
    int type;
    parser(std::string,std::string);
    int parse();
    std::vector<std::vector<int>> &getMaze();
    std::vector<std::vector<int>> &getModules();
    std::string returninfo;
private:
    std::string filename;
};