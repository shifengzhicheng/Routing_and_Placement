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

我们的项目完成了布局布线算法中的两个部分

- 迷宫布局布线算法
- `FM`算法实现的划分

### 创新点

1. 使用工厂模式实现主要的功能，各部分抽象程度高，且可扩展性很强
2. `Astar`算法使用了优先队列实现，使用简单的连线策略实现了多数情况下相对优的连线结果。
3. `Astar`生成多点的连线的算法我们采取了以下策略：
   - 增加尝试创建布线的边权重
   - 将已布线边的权重降低为0
3. `FM`算法实现了通过桶型数据结构查找最大增益和相应的更新，在大数据量的背景下对于算法时间复杂度的优化显得极为必要，同时使用多起始点方法改进`FM`算法。 

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

在`file`中有一个计算`Astar`布线长度的程序，原理是利用两个存储矩阵的文件中的矩阵做差然后计算布线线长。在`file`文件夹中执行如下命令：

```bash
.\Calc.exe file1 file2
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
│# 编译项目的Makefile,Windows下使用MinGW32编译
│   Makefile
│# 项目的说明文档
│   README.md
│   README.pdf
│# 项目的可执行文件（Windows平台下）
│   Routing.exe
│# 项目的测试文件以及输出
├───file
│# 项目的README中的图片
├───picture
│# 项目的参考文件
├───projectfile
│# 项目的源文件
└───src
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

这部分由邱峻蓬同学、任钰浩同学和沈笑涵同学共同完成，邱峻蓬同学主要负责了FM算法的代码实现和改进。

#### 算法概述

##### 介绍

`FM`算法的移动过程和`KL`算法很类似。目标都是讲割代价最小化。但是`FM`算法要`i`计算每个独立节点移动的增益，而不是对交换所产生的增益。和`KL`算法一样，`FM`算法再每个轮次中选择最好的一次移动。在`FM`算法的每轮中，一旦一个节点被移动，在本轮中它就被锁定不能再次移动。

##### 术语

以下是和`FM`算法有关的定义

节点 $c$ 的增益 $\Delta g(c)$ 是 $c$ 移动后割集割边数量所产生的变化。增益 $\Delta g(c)$ 越高，移动节点 $c$ 到其它划分的的优先级越高。形式上，节点增益被定义为 ：

$$
\Sigma_{i=1}^m \Delta g_i
$$

其中 $E(c)$ 是 $c$ 与不是其所在划分的节点之间边的数量，$I(c)$ 是 $c$ 与其自身所在划分的其它节点之间边的数量。

每轮中的最大增益 $G_m$ 是指 $m$ 次移动所产生的最大节点增益 $\Delta g$ 的总和所决定的。

$$
\Sigma_{i=1}^m \Delta g_i
$$

类似于在`KL`算法中，每轮中所有的移动决定了 $G_m$ 和移动顺序 $\{c_1...c_m\}$ 在每轮结束后，即 $G_m$ 和相应的 $m$ 次移动被决定后，再更新移动节点的位置。

##### 流程伪代码

我们为算法流程写了一个简单的伪代码供参考：

```php
INPUT: 图 G(V,E)
OUTPUT: 划分后的图 G(V,E)
(A, B) = PARTITION(G) //划分初始化
G_m = \infin
while (G_m > 0) {
    i = 1
    order = \emptyset
    foreach (c \in V) {
        \Delta g[i][c] = E(c) - I(c) //计算所有节点的初始增益
        status[c] = FREE //将所有节点设为自由
    }
    while (!IS_FIXED(V)) {
        cell = MAX_GAIN(\Delta g[i]) //找到增益最大的节点
        ADD(order, (cell, \Delta g[i])) //记录节点移动序列
        cirtical_net = CRITICAL_NETS(cell) //连接该节点的线网
        if (cell \in A) {
            TRY_MOVE(cell, A, B)
        } else {
            TRY_MOVE(cell, B, A)
        }
        status[cell] = FIXED
        foreach (c \in critical_net, c \neq cell) {
            if (status[c] == FREE) {
                UPDATE_GAIN(\Delta g[i][c]) //更新与尝试移动节点相连的所有节点的增益
            }
        }
        i = i + 1
    }
    (G_m, m) = BEST_MOVES(order) //找到 G_m 最大化时的移动序列
    if (G_m > 0) {
        CONFIRM_MOVES(order, m) //按该移动序列进行实际移动操作
    }
}
```
#### 算法具体实现
│   ├── `data_structure.h`

│   ├── `FM_algorithm.h`

│   ├── `FM_algorithm.cpp`

##### 节点类的定义

```c++
class NODE {
public:
	int nodeIndex;                           //节点索引
	NODE_PART Node_Partition;                //节点划分归属
	LOCK_STATE lockedstate;                  //节点锁定情况
	int nodeGain;                            //节点增益
	std::vector<int> ConnectedNode;          //节点连接的其他节点
}
```
对于`NODE`类，重载了三个构造函数以便灵活赋值。

##### 节点的指针数组类

```c++
class POINTER_ARRAY {
public:
	std::vector<NODE*> data_array;                                       //节点的指针数组

	POINTER_ARRAY();
	POINTER_ARRAY(std::vector<std::vector<int>>& modules);               //根据parser解析得到的modules进行指针数组的构造
	void copy(POINTER_ARRAY pa);                                         //指针数组的复制
	void reset(POINTER_ARRAY pa);                                        //指针数组的拷贝赋值
	void recover();                                                      //指针数组的解锁
	void init_half();                                                    //指针数组的二分初始化划分
	void init_even();                                                    //指针数组的奇偶初始化划分
	void init_rand();                                                    //指针数组的随机初始化划分
	void updateGain();                                                   //指针数组更新增益
	int updateGain(int i);                                               //指针数组更新指定节点增益
	int cutSize();                                                       //指针数组按照当前划分被切割的边数
};
```

##### 桶结构类

```c++
class BucketNode {
public:
	int nodeIndex;
	BucketNode* next;
	BucketNode* prev;
	BucketNode(int i,BucketNode* n,BucketNode* p) {
		nodeIndex = i;
		next = n;
		prev = p;
	}
};
class Bucket {
public:
	std::map<int, BucketNode*, std::greater<int>> bucketAtoB;
	std::map<int, BucketNode*, std::greater<int>> bucketBtoA;

	Bucket()；
	void load(POINTER_ARRAY& parr)；
	int maxGain(NODE_PART partition,POINTER_ARRAY& parr)；
	void updateLocal(NODE_PART partition, int i, int updateGain, int prevGain)；
};
```
桶结构中为了减少数据冗余，新定义了桶节点以实现双向链表结构。采用`map`容器来构造桶形结构，使得可以通过增益值作为桶的入口来访问节点，由于`map`容器本身的自排序性，可轻松找到增益最大的入口。
由于实现的目标是二划分，因此需要对两个方向分别维持一个桶形数据结构。

##### FM类

```c++
class FM {
public:
    int mincutsize;								// FM算法执行后当前的最小切割数
	void one_swap(
        Bucket& bu, 
        POINTER_ARRAY& pointer_array_local, 
        POINTER_ARRAY& pointer_array_global, 
        int currentBest
    );											// FM算法的一次迭代
	std::vector<std::vector<int>> FM_Algorithm(
        std::vector<std::vector<int>> modules
    );                                          //FM算法
	std::vector<std::vector<int>> FM_Algorithm_Pertubation(
        std::vector<std::vector<int>> modules
    );                                			//加入初始状态微扰后改进的FM算法
};
```
`one_swap`方法即通过桶形数据结构和节点指针数组执行如下过程：从`partition A`中取得最大增益且未锁定的节点移动至`partition B`中，更新`A`节点相连所有节点的增益；从`partition B`中取得最大增益且未锁定的节点移动至`partition A`中，更新`B`节点相连所有节点的增益。直到所有节点都被锁定后，完成一次迭代。
`FM`算法中宏定义了迭代的上限`MaxIteration`，但为了加快`FM`算法的运算过程，假设连续两次迭代都未能成功减小切割数后即结束算法。

由于`FM`算法基于邻域搜索，因此初始解的情况会非常明显的影响FM算法的最优结果。例如，当`FM`算法的初始解按照前1000个节点和后1000个节点划分时，`FM`算法所得最小切割边数为`1144`。

<img src="picture\fm_half.png" alt="fm_half" width="600px;" />

当`FM`算法的初始解按照奇偶节点划分时，`FM`算法所得最小切割边数为`1123`。

<img src="picture\fm_even.png" alt="fm_even" width="600px;" />

因此，对于`FM`算法做出多起始点方法的改进，通过随机数产生随机初始平衡划分，多次运行寻找最优结果作为最终的划分结果。因此`FM_Algorithm_Pertubation`的执行结果具体到每一次都不尽相同，但从数学统计意义上可以给出最优结果。本实现中重复运行`5`次基础`FM`算法。一次典型的运行结果如下。

<img src="picture\fm_rand.png" alt="fm_rand" width="600px;" />

### Part 2`Astar`算法实现模块的连线

这部分由郑志宇同学和周翔同学完成。

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
#### 文件解析
该部分将记录数据信息的.txt文件读入并转化为`FM`算法和`Astar`算法需要的的数据结构
详见以下文件：

│   ├── `parser.cpp`

│   ├── `parser.h`

其中`Maze`中存`Astar`算法所需要的数据，`Modules`中存`FM`算法所需要的数据，`erroinfo`中存读取文件时发现的文件格式错误信息，通过相应的`getMaze``getModules``returninfo`等结构访问数据与信息
```C++
class parser
{
public:
    int type;
    parser(std::string, std::string);
    int parse();
    std::string returninfo();
    std::string getFileName();
    std::vector<std::vector<int>>& getMaze();
    std::vector<std::vector<int>>& getModules();
private:
    std::string filename;
    std::string erroinfo;
    std::vector<std::vector<int>> Maze;
    std::vector<std::vector<int>> Modules;
};
```
#### 结果显示
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
    int source, int target, std::vector<int> &parent);
    // 矩阵
    std::vector<std::vector<int>> Maze;
    // 模块连接关系
    std::vector<std::vector<int>> modules;
    // 划分
    std::vector<std::vector<int>> partition;
    // Astar代理
    AStarGraph Astar;
    // FM算法实现代理
    FM fm;
};
```
其中，`modules`为通过`parser`对输入解析后得到的结果，`type`标志了该解析文件后的输出类型，
`Maze`和`fm`分别存储`Astar`和`FM`算法得到的结果。

`int cost_of_routing_Astar()`和`int cost_of_FM();`两个函数为计算`Astar`和`FM`算法得到的结果的代价。具体来说，`Astar`算法的代价为布线线长，`FM`算法的代价为切割边的值。
最后，通过`outputfile()`函数将结果写入到txt文件中。


## 项目测试

### 测试文件1 `prob1.txt`

#### 输出结果 `outputprob1.txt`

```bash
partition size: 1000: 
1 3 5 6 7 ...
partition size: 1000: 
0 2 4 10 ...
```
```bash
cut size: 1113
```
可以看到结果中两组划分个数相同，且最小切割边数目为1113。

### 测试文件2 `prob4.txt`

#### 输出结果 `outputprob4.txt`

```bash
0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 3 3 3 3 3 3 3 2 3 3 3 0 1 
0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 3 1 0 1 0 0 0 0 0 0 2 0 1 
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 0 0 0 0 0 0 1 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 0 0 0 1 0 0 0 1 0 0 0 0 
...
```
`Astar`代价如下：
<img src="picture\LineLength.png" alt="image-20230618135617180" width="600px" />

在我们使用的简单的优化策略之下，总连线线长为168。

## 项目总结

我们的项目旨在完成布局布线算法中的两个关键部分：迷宫布局布线算法和使用FM算法进行划分。在项目中，我们引入了工厂模式来实现主要功能，以提高代码的抽象程度和可扩展性。

在迷宫布局布线算法中，我们采用了Astar算法，并使用优先队列来实现快速搜索和路径选择。我们还实现了简单的连线策略，以在大多数情况下得到相对优秀的连线结果。对于Astar算法生成多点的连线，我们采用了一些策略来优化结果。首先，我们增加了尝试创建布线的边的权重，以鼓励算法在这些位置上进行连线。其次，已经布线的边的权重被降低为0，以避免重复布线。

在FM算法的实现中，我们采用了桶型数据结构来查找最大增益并进行相应的更新。这种方法在处理大规模数据时，对算法的时间复杂度进行了优化。此外，我们还引入了多起始点的方法来改进FM算法的性能和效果。

通过我们的项目，我们取得了以下创新点和成果：

1. 引入工厂模式，提高了代码的抽象程度和可扩展性。
2. Astar算法的优先队列实现和连线策略，实现了大多数情况下较好的连线结果。
3. 通过增加边权重和降低已布线边的权重，优化了Astar算法生成多点连线的结果。
4. FM算法的桶型数据结构和多起始点方法，提高了算法在大数据量背景下的时间复杂度和性能。

总的来说，我们的项目在布局布线算法中取得了一定的创新和成果，提高了算法的效率和质量。然而，仍有进一步的改进空间，可以继续研究和优化算法，以满足更复杂和多样化的布局布线需求。
