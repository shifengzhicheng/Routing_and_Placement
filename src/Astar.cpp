#include"Astar.h"
#include <queue>
void AStarGraph::addEdge(int s, int e, double w) {
    if (s < v_count_ && e < v_count_) {
        adj_[s].emplace_back(s, e, w);
    }
}

void AStarGraph::addVertex(int id, int x, int y) {
    if (id < v_count_) {
        vertexes[id] = Vertex(id, x, y);
    }
}

std::vector<int> AStarGraph::AStar(int s, int e) {
    // 与 Dijkstra 的区别主要在以下几点:
    // 1、优先队列的构建方式不同，A* 算法是使用代码中public int f;这个值来构建的，而 Dijkstra 算法是用 dist 值构建的
    // 2、A* 算法除了需要更新 dist 值，还需要更新 f 值。
    // 3、A* 算法循环结束的条件是只要遍历到终点即退出循环，因此 A* 算法最终并不一定能得到最短路径。
    std::vector<int> parent(v_count_); // 用于还原最短路径, 当前点最短路径的父节点
    struct cmp {
        bool operator() (const Vertex& v1, const Vertex& v2) { return v1.f_ > v2.f_; }
    };
    // 最小堆
    std::priority_queue<Vertex, std::vector<Vertex>, cmp> queue;
    // 标记是否已找到最短距离
    std::vector<bool> shortest(v_count_, false);

    // 起始节点初始化
    vertexes[s].dist_ = 0;
    vertexes[s].f_ = 0;
    queue.push(vertexes[s]);
    while (!queue.empty()) {
        Vertex minVertex = queue.top();
        queue.pop();
        if (minVertex.id_ == e) { break; }
        if (shortest[minVertex.id_]) { continue; } // 之前更新过，是冗余备份
        shortest[minVertex.id_] = true;
        for (int i = 0; i < adj_[minVertex.id_].size(); ++i) {
            Edge cur_edge = adj_[minVertex.id_].at(i); // 取出当前连通的边
            int next_vid = cur_edge.eid_;
            if (minVertex.dist_ + cur_edge.w_ < vertexes[next_vid].dist_) {
                vertexes[next_vid].dist_ = minVertex.dist_ + cur_edge.w_;
                vertexes[next_vid].f_ = vertexes[next_vid].dist_ +
                    hManhattan(vertexes[next_vid].x_, vertexes[next_vid].y_,
                        vertexes[e].x_, vertexes[e].y_);
                parent[next_vid] = minVertex.id_;
                queue.push(vertexes[next_vid]);
            }
        }
    }
    return parent;
}

void AStarGraph::Initial()
{
    for (auto Ver:vertexes) {
        Ver.dist_ = std::numeric_limits<double>::max();
        Ver.f_ = std::numeric_limits<double>::max();
    }
}

void AStarGraph::CreateGraph(std::vector<std::vector<int>>& _Maze)
{
    int ysize = _Maze.size();
    int xsize = _Maze[0].size();
    v_count_ = xsize * ysize;
    adj_ = std::vector<std::vector<Edge>>(v_count_, std::vector<Edge>{});
    vertexes = std::vector<Vertex>(v_count_);
    int CurNode = 0;
    std::vector<int> addx({ 1,0,-1,0 });
    std::vector<int> addy({ 0,1,0,-1 });
    for (int y = 0; y < _Maze.size(); y++) {
        for (int x = 0; x < _Maze[0].size(); x++) {
            addVertex(CurNode, x, y);
            if (_Maze[y].at(x) == 2) {
                ConnectionPoint.push_back(CurNode);
            }
            for (int i = 0; i < addx.size(); i++) {
                int Nextx = x + addx[i];
                int Nexty = y + addy[i];
                if (
                    Nextx >= xsize ||
                    Nexty >= ysize ||
                    Nextx < 0 ||
                    Nexty < 0 ||
                    _Maze[Nexty].at(Nextx) == 1
                    ) {
                    continue;
                }
                int NextNode = Nextx + Nexty * xsize;
                addEdge(CurNode,NextNode,1);
            }
            CurNode++;
        }
    }
}
