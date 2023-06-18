#include <iostream>
#include "parser.h"
#include "Routing.h"
// int main()
// {
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Error, Usage:" << argv[0] << "Operation(FM or Astar)"
                  << "filename\n";
        return -1;
    }
    // 创建解析器对象
    std::string type = argv[1];
    std::string filename = argv[2];
    parser p(type, filename);
    if (p.parse() != 0)
    {                                                             // 执行解析，为0时解析成功
        std::cout << "parsing error, " << p.returninfo() << "\n"; // 输出解析错误信息
        return -1;                                                // 返回错误状态码
    }
    // 创建一个Routing and Placement的对象
    Routing RP(p);
    // 选择操作
    switch (RP.type)
    {
    case OPFM:
        RP.performFM();
        RP.filename = filename;
        break;

    case OPAstar:
        RP.performAstar();
        RP.filename = filename;
        break;
    }
    // 输出文件
    RP.outputfile();
}
