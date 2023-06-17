#include "Routing.h"
#include <fstream>
#include <iostream>
//Routing::Routing(parser &p)
//{
//}

void Routing::performFM()
{
}

void connect(std::vector<std::vector<int>>& Maze, int source, int target, std::vector<int> parent)
{
	if (source == target) return;
	int x = target % Maze[0].size();
	int y = target / Maze[0].size();
	if (Maze[y].at(x) != 2) {
		Maze[y].at(x) = 3;
	}
	connect(Maze, source, parent[target], parent);
}

void Routing::performAstar()
{
	Astar.CreateGraph(Maze);
	std::vector<int> ConnectionPoint = Astar.getConnectionPoint();

	for (int i = 0; i < ConnectionPoint.size() - 1; i++)
	{
		std::vector<int> parent = Astar.AStar(ConnectionPoint[i], ConnectionPoint[i + 1]);
		connect(Maze, ConnectionPoint[i], ConnectionPoint[i + 1], parent);
		Astar.Initial();
	}

	//for (int i = 0; i < Maze.size(); i++) {
	//	for (int j = 0; j < Maze[0].size(); j++)
	//		std::cout << Maze[i][j];
	//	std::cout << "\n";
	//}
}




void Routing::outputfile()
{
	std::string filepath(filename + "out.txt");
	std::ofstream output_file(filepath);
	if (!output_file.is_open()) {
		std::cerr << "Failed to open output file!" << std::endl;
		return;
	}
	for (auto i : Maze) {
		for (auto value : i)
			output_file << value << " ";
		output_file << std::endl;
	}
	// 关闭文件
	output_file.close();
	std::cout << "Output file: " << filepath << std::endl;
}
