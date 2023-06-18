# Routing_and_Placement
FM算法以及Astar算法实现读取文件进行处理

## 项目说明文档

### 划分问题

#### 题目介绍与题目要求

考虑二划分问题，对给定的节点集合进行二划分，划分目标是平衡最小割。可以使用FM算法来实现。提供一个描述节点连接关系的文件prob1.txt

#### 文件示例：

```tcl
19
3 5 7 19
4 5 1
10 11
3 6
…
```

其中第一行表示节点数，比如19。后面跟随19行，表示从1-19个节点分别连接的节点。

### 迷宫算法布线

#### 题目介绍与题目要求

本题需要实现的是迷宫布线算法。可以采用原始迷宫算法，也可以实现改进的A*迷宫算法。迷宫的全重假设为1。布线后的占据的迷宫位置要成为新的障碍。

本题给定prob4.txt文件，描述的是一个矩阵，每一位表示该坐标上的路径状态：0表示无障碍，1表示障碍，2表示有要连接的引脚。本题需要用迷宫布线算法将引脚都连接上，并且绕过障碍物。

#### 文件示例：

```tcl
0 0 0 0 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 1 0
0 0 2 0 0 0 0 0 0 1
0 0 0 2 0 2 0 0 0 1
0 0 0 2 0 0 0 0 0 0
0 0 2 0 0 2 0 0 2 0
```

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
2. 

### 项目使用方法

#### 环境要求

- `visual studio 2019`及以上版本能正常打开项目中的所有文件
- 注意`src`编码格式为`Unicode(UTF-8)`
- 生成一个`Routing.exe` 的可执行文件能够在`windows` 下运行。如果想要生成`Linux`下的`Makefile`，可以修改一下`Makefile`文件。

#### 使用方式

根据自己的环境编写替换`Makefile`，目前项目中的`Makefile`仅仅适用于`window`。

`Windows`：在`file` 文件夹中写好测试文件`file.txt` 后，在项目文件夹下运行以下命令：

```bash
.\Routing.exe FM file\file.txt
.\Routing.exe Astar file\file.txt
```

#### cmd中运行结果示意：

```bash
# partition迭代次数
FM ..
iteration 0: Cut Size = ...
iteration 1: Cut Size = ...
iteration 2: Cut Size = ...
FM algorithm .. done. Cut Size = ...
Partition Result:
# Astar输出一个连好线的图
0 0 0 0 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 1 0 
0 0 2 3 0 0 0 0 0 1 
0 0 0 2 3 2 0 0 0 1 
0 0 0 2 3 3 0 0 0 0 
0 0 2 3 3 2 3 3 2 0 
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

此部分由郑志宇同学搭建，接口与功能与小组成员共同商议确定。最终实现了项目的并行推进与项目成员对函数的独立维护。方便项目更容易进行其他功能的扩展。最终有郑志宇同学完成了项目的编译，输出一个`Routing.exe`文件。

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

这部分由邱峻蓬同学，任钰浩同学，沈笑涵同学完成。

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

###### `AStarGraph`类

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

在电路图中，虽然不知道中间某个点距离终点的最短路，但是我们可以将地图置于坐标轴中，通过计算节点之间的曼哈顿距离来代替欧几里得距离，曼哈顿距离就是计算两点之间横纵坐标的距离之和，只涉及到加减法和符号转换。这里得到的距离记为$h(i)$，作为启发函数。

而$g(i) + h(i)$就可以当做最终的估价函数，优先队列中，估价函数值最低的优先出列。
$$
f(i) = g(i) + h(i)
$$

#### 连接多个点的策略

│   ├── `routing.h`
│   ├── `routing.cpp`

##### `connect`函数

```C++
void connect(std::vector<std::vector<int>>& Maze, int source, int target, std::vector<int> &parent)
{
	if (source == target) return;
	int x = target % Maze[0].size();
	int y = target / Maze[0].size();
	if (Maze[y].at(x) != 2) {
		Maze[y].at(x) = 3;
	}
	connect(Maze, source, parent[target], &parent);
}
```
`AStarGraph.AStar(int s, int e)`会传出全部的搜索结果`parent`，是一个大小为`n*n`的向量。如果直接通过`for`循环更改`Maze`的所有的参数，可能会出现两个引脚之间存在多条连线的情况。这里使用递归，由目标节点向前推进，直到回到开始节点为止。期间可能会经过其他引脚，此时不改变`Maze`中该引脚位置的参数。否则将`Maze`上的参数改为`3`，表示连线经过该点。

##### `performAstar`函数

```C++
void Routing::performAstar()
{
	Astar.CreateGraph(Maze);
	std::vector<int> ConnectionPoint = Astar.getConnectionPoint();

	for (int i = 0; i < ConnectionPoint.size() - 1; i++)
	{
		Astar.Initial();
		std::vector<int> parent = Astar.AStar(ConnectionPoint[i], ConnectionPoint[i + 1]);
		connect(Maze, ConnectionPoint[i], ConnectionPoint[i + 1], parent);
	}
	Astar.drawGrid(Maze);
}

```
由于每次利用`Astar`算法对两个引脚进行连线后，都会改变图`Maze`上节点的参数，因此在进行下一次布线之前，首先需要使用`Astar.Initial()`函数进行初始化，将节点的`dist_`与`f_`恢复到最大值，之后再进行后续节点的`connect`操作。

##### 连接的策略

###### 采用的策略

我们在连接点的时候采用的策略会自动优化一部分线长。但是由于我们实质上并没有尝试引入斯坦纳点去解决最小生成子树的问题，所以连出的线中仍有可以优化的部分。实际上我们可以优化点之间连接的顺序来实现这个工作。由于时间关系，我们将这个工作放在以后。

实际上我们在连接点的时候，我们使用了这样的策略：

1. 需要连线的点按照从上到下，从左到右的顺序进行记录。这种记录方式实际上会导致一些连线的浪费问题。我们考虑使用优先队列来实现这样一个连线的问题或许会更好一些。但程序中并没有这样做。
2. 已经连过的走线我们将它的代价视为`0`，这样节点在同样的曼哈顿距离下会优先选择连好的线。
3. 没有连过的走线我们将它的代价设为`1.1`。这样实际上会让节点之间在连线时在有可能的情况下不会因为路径进入队列的顺序问题而产生额外的走线。

###### 结果的对比

下面是我们优化过程中得到的中间文件的对比情况，供参考：

使用`Calcdifference.cpp`编译了一个`Calc.exe`文件来实现这种代价的对比。

使用方式：

```bash
Calc.exe file1 file2
```

实现两个文件中矩阵作差并求出线长的差距。

<img src="picture\AstarCompar.png" alt="image-20230618135206312" width="600px" />

对比了最初没有做优化以及加入了策略2和策略3之后得到的线长的优化长度。可以看到优化还是较为明显的。以下是总线长的计算。

<img src="picture\LineLength.png" alt="image-20230618135617180" width="600px" />

### Part 3 文件解析以及`FM`算法和`Astar`算法实现结果的显示

该部分由任钰浩和沈笑涵同学完成。
该部分实现了将前两部分`FM`和`Astar`算法的结果汇总，并完成相关布线代价的计算，并将最终布线结果输出到txt文件中。其部分详见以下文件：

│   ├── `routing.cpp`

│   ├── `routing.h`

其中，`routing.h`中构造了一个`Routing`的class，基本结构如下：
```C++
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
private:
    void connect(std::vector<std::vector<int>>& Maze, 
    int source, int target, std::vector<int> parent);
    // 矩阵
    std::vector<std::vector<int>> Maze;
    // 模块连接关系
    std::vector<std::vector<int>> modules;
    // 划分
    std::vector<std::vector<int>> partition;
    // Astar代理
    AStarGraph Astar;
    // FM代理
    FM fm;
};
```
其中，`Maze`和`fm`分别存储`Astar`和`FM`算法得到的结果。

其中，`Astar`算法的代价为布线线长，`FM`算法的代价为最小比例切割边的值。
最后，通过`outputfile()`函数将结果写入到txt文件中。


## 项目测试

### 测试文件1 `prob1.txt`

#### 输出结果 `outputprob1.txt`

```bash

```

### 测试文件2 `prob4.txt`

#### 输出结果 `outputprob4.txt`

```bash
0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 3 3 3 0 1 
0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 0 3 3 3 3 2 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 1 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 1 0 0 0 1 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 1 0 0 0 0 1 0 0 
0 0 0 0 0 0 0 0 0 0 2 3 3 3 3 3 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 3 3 3 3 3 3 3 3 2 
0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 2 
1 0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 
0 1 0 0 1 0 0 1 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 0 0 0 0 
0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 1 0 0 0 
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1 1 0 0 0 0 0 1 0 0 3 3 3 3 2 
1 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 
0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 2 3 3 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 1 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 3 2 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 3 1 0 0 0 0 0 1 0 0 0 1 0 0 0 0 
0 0 0 0 1 0 0 0 1 0 1 1 0 0 3 3 3 3 3 3 3 3 3 3 3 2 0 0 0 0 0 0 0 1 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 1 0 0 0 0 2 3 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 1 0 0 1 0 0 0 0 0 0 0 3 3 3 3 3 2 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 1 0 
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 
0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 0 1 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 
0 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 
0 0 0 0 0 0 0 0 0 2 3 3 3 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 3 3 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 1 0 0 0 0 0 3 3 3 3 2 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 0 0 2 3 3 3 3 3 3 3 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
0 0 0 2 3 3 3 3 3 3 3 3 3 3 3 1 0 0 0 1 0 0 0 0 0 3 3 3 1 0 2 3 3 3 3 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 1 3 3 3 3 0 0 0 3 3 1 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 3 3 0 0 0 
0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 1 0 1 0 1 1 0 0 0 0 0 0 0 0 0 3 3 3 3 3 2 1 0 0 
0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 1 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 3 3 3 3 3 1 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 3 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 2 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
```
`Astar`代价如下：
<img src="picture\LineLength.png" alt="image-20230618135617180" width="600px" />

在我们使用的简单的优化策略之下，总连线线长为168。

## 项目总结



