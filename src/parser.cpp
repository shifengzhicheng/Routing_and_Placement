#include "parser.h"
#include "Point.h"
#include <fstream>
#include <iostream>


parser::parser(std::string type, std::string filename)
{
	if (type == "FM")
		this->type = OPFM;
	else if (type == "Astar")
		this->type = OPAstar;
	this->filename = filename;
}

std::vector<std::vector<int>>& parser::getModules()
{
	return Modules;
}

std::vector<std::vector<int>>& parser::getMaze()
{
	return Maze;
}

std::string parser::returninfo()
{
	return erroinfo;
}

int parser::parse()
{
	if (type == OPFM)
	{
		std::ifstream myfile(filename);
		if (!myfile.is_open())
		{
			erroinfo = "file not open";
			return 1;
		}
		else
		{
			std::string numStr;
			std::getline(myfile, numStr);
			int num = std::stoi(numStr);
			Modules.resize(num);
			std::string line;
			while (std::getline(myfile, line))
			{
				std::string tmp;
				bool isIndex = true;
				int index = -1;
				for (int i = 0; line[i] != '\0'; i++)
				{
					if (line[i] != ' ')
						tmp += line[i];
					else
					{
						if (isIndex)
						{
							index = std::stoi(tmp);
							tmp = "";
							isIndex = false;
						}
						else
						{
							if (index >= num)
							{
								erroinfo = "node overflow";
								return 1;
								break;
							}
							else
							{
								Modules[index].push_back(std::stoi(tmp));
								tmp = "";
							}
						}
					}
				}
				if (index >= 0)
					Modules[index].push_back(std::stoi(tmp));
			}
			return 0;
		}
	}
	else
	{
		std::ifstream myfile(filename);
		if (!myfile.is_open())
		{
			erroinfo = "file not open";
			return 1;
		}
		else
		{
			std::string line;
			while (std::getline(myfile, line))
			{
				Maze.push_back(std::vector<int>());
				std::string tmp = "";
				for (int i = 0; line[i] != '\0'; i++)
				{
					if (line[i] != ' ')
						tmp += line[i];
					else
					{
						(Maze.end() - 1)->push_back(std::stoi(tmp));
						tmp = "";
					}
				}
			}
			return 0;
		}
	}
}
