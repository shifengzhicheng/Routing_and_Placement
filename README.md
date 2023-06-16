# Routing_and_Placement
FM算法以及Astar算法实现读取文件进行处理

## 项目说明文档

### 划分问题

#### 题目介绍与题目要求

考虑二划分问题，对给定的节点集合进行二划分，划分目标是平衡最小割。可以使用FM算法来实现。提供一个描述节点连接关系的文件prob1.txt

#### 文件示例：

19

3 5 7 19

4 5 1

10 11

3 6

…

其中第一行表示节点数，比如19。后面跟随19行，表示从1-19个节点分别连接的节点。

### 迷宫算法布线

#### 题目介绍与题目要求

本题需要实现的是迷宫布线算法。可以采用原始迷宫算法，也可以实现改进的A*迷宫算法。迷宫的全重假设为1。布线后的占据的迷宫位置要成为新的障碍。

本题给定prob4.txt文件，描述的是一个矩阵，每一位表示该坐标上的路径状态：0表示无障碍，1表示障碍，2表示有要连接的引脚。本题需要用迷宫布线算法将引脚都连接上，并且绕过障碍物。

#### 文件示例：

0 0 0 0 0 0 0 0 0 0 

1 0 0 1 0 0 0 0 1 0

0 0 2 0 0 0 0 0 0 1

0 0 0 2 0 2 0 0 0 1

0 0 0 2 0 0 0 0 0 0

0 0 2 0 0 2 0 0 2 0

## 项目成员

| 成员名称 | 学号        |
| -------- | ----------- |
| 郑志宇   | 20307130176 |
| 邱峻蓬   | 20307130028 |
| 任钰浩   | 20307130243 |
| 沈笑涵   | 20307130063 |
| 周翔     | 20307130188 |

## 项目说明

### 功能说明

### 创新点

1. 使用工厂模式实现主要的功能，各部分抽象程度高，且可扩展性很强
2. `Astar`算法使用了优先队列实现，使用简单的连线策略实现了多数情况下相对优的连线结果。

### 项目使用方法

#### 环境要求

- `visual studio 2019`及以上版本能正常打开项目中的所有文件
- 注意`src`编码格式为`Unicode(UTF-8)`
- 生成一个`Routing.exe` 的可执行文件能够在`windows` 下运行。如果想要生成`Linux`下的`Makefile`，可以修改一下`Makefile`文件。

#### 使用方式

根据自己的环境编写替换`Makefile`，目前项目中的`Makefile`仅仅适用于`window`。

`Windows`：在`testfile` 文件夹中写好测试文件`file.ll` 后，在项目文件夹下运行以下命令：

```
.\Routing.exe FM testfile\prob1.txt
.\Routing.exe Astar testfile\prob4.txt
```

#### cmd中运行结果示意：

```bash


```

### 文件格式声明

#### FM算法支持的文件格式

```ini
19
3 5 7 19
4 5 1
10 11
3 6
...
```

其中第一行表示节点数，比如19。后面跟随19行，表示从1-19个节点分别连接的节点。

#### Astar算法支持的文件格式

```ini
0 0 0 0 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 1 0
0 0 2 0 0 0 0 0 0 1
0 0 0 2 0 2 0 0 0 1
0 0 0 2 0 0 0 0 0 0
0 0 2 0 0 2 0 0 2 0
```

上面的文件描述的是一个矩阵，每一位表示该坐标上的路径状态：0表示无障碍，1表示障碍，2表示有要连接的引脚。

## 项目的结构

```bash
├── picture # README文档的说明图片
├── projectfile # 项目要求文档与参考资料
│   ├── read.md # 项目要求文件
##### 输出和输入文件	
├── file 
│   ├── prob1.txt
│   ├── prob4.txt
##### 源文件
├── src
│   ├── main.cpp
##### 
├── README.md # 项目文档
├── Makefile # windows平台下的makefile
├── Routing.exe # windows平台下编译的结果，使用mingw32_make
```

## 项目技术细节

### 项目顶层文件

此部分由郑志宇同学搭建，接口与功能与小组成员共同商议确定。最终实现了项目的并行推进与项目成员对函数的独立维护。方便项目更容易进行其他功能的扩展。

│   ├── `main.cpp`

│   ├── `routing.cpp`

│   ├── `routing.h`

#### 顶层的流程

- `parser`类读取文件并解析，得到对应的对象
- `Routing`类根据解析文件的结果实现不同的功能
  - `Astar`连线
  - `FM`划分
- `Routing`类输出一个文件到目标文件夹`file`

### Part 1`FM`算法实现模块的划分



### Part 2`Astar`算法实现模块的连线

这部分由郑志宇同学与周翔同学共同完成。

#### 点到点的`A*`算法

│   ├── `Astar.h`

│   ├── `Astar.cpp`

##### `A*`算法图的定义

###### 边和节点定义

```c++
struct Edge
{              // 表示边
    int sid_;  // 边的起始节点
    int eid_;  // 边的结束节点
    double w_; // 边的权重
    Edge() = default;
    Edge(int s, int e, double w)
        : sid_(s), eid_(e), w_(w) {}
};
struct Vertex
{
    int id_;
    double dist_; // 算法实现中，记录第一个节点到这个节点的距离
    double f_;    // f(i)=g(i)+h(i)
    int x_, y_;   // 顶点在地图中的坐标（x, y）
    Vertex() = default;
    Vertex(int id, int x, int y)
        : id_(id), x_(x), y_(y), dist_(std::numeric_limits<double>::max()), f_(std::numeric_limits<double>::max()) {}
};
```

###### `AstarGraph`类

```c++
class AStarGraph
{
public:
    AStarGraph(){};
    void CreateGraph(std::vector<std::vector<int>> &_Maze); // 创建图
    void addEdge(int s, int e, double w);                   // 添加边
    void addVertex(int id, int x, int y);                   // 添加节点
    std::vector<int> AStar(int s, int e);                   // 寻路
    void Initial();                                         // 初始化
    std::vector<int> &getConnectionPoint()                  // 返回需要连接的点的关系
    {
        return ConnectionPoint;
    };
private:
    std::vector<std::vector<Edge>> adj_; // 邻接表
    int v_count_;                        // 顶点数
    std::vector<Vertex> vertexes;        // 记录所有顶点，主要记录坐标
    double hManhattan(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
    std::vector<int> ConnectionPoint;
};
```

##### `A*`算法是对`Dijkstra`算法的优化

在`Dijkstra`算法中，需要创建了优先队列，从优先队列中取出节点，再从这个节点扩散到其他节点（类似广度优先搜索），优先队列的优先依据是根据起始点到队列中节点最近的一个。即队列中的节点总是离起始点最近的先出队，这样很容易在一开始就跑偏。

当走到某个节点时，已知的是起始点到该节点的距离$g(i)$，`Dijkstra`算法判断依据就只有这一个，那么再增加一个当前节点到终点的距离，结合$g(i)$可以实现防止过度跑偏。

在电路图中，虽然不知道中间某个点距离终点的最短路，但是我们可以将地图置于坐标轴中，通过计算节点之间的曼哈顿距离来代替欧几里得距离，曼哈顿距离就是计算两点之间横纵坐标的距离之和，只涉及到加减法和符号转换。这里得到的距离记为$h(i)$，为启发函数。

而$g(i) + h(i)$就可以当做最终的估价函数，优先队列中，估价函数值最低的优先出列。
$$
f(i) = g(i) + h(i)
$$

#### 连接多个点的策略

│   ├── `routing.h`

```C++

```

## 项目测试

### 测试文件1 `prob1.txt`

#### 输出结果 `outputprob1.txt`

```bash

```

### 测试文件2 `prob4.txt`

#### 输出结果 `outputprob4.txt`

```bash

```

## 项目总结



