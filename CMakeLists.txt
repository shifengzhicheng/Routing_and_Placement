# 设置最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(RoutingAndPlacement)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG -Wall -Wextra -fPIC")

# 源文件和头文件目录
set(SRC_DIR src)
file(GLOB SOURCES "${SRC_DIR}/*.cpp")
file(GLOB HEADERS "${SRC_DIR}/*.h")

# 可执行文件目标1：主程序
add_executable(main ${SOURCES})

# 链接库（如果有需要）
target_link_libraries(main ${CMAKE_DL_LIBS})

# 可执行文件目标2：file文件夹中的单独程序
add_executable(CalcDifference file/Calcdifference.cpp)