#ifndef FM_ALGORITHM_H
#define FM_ALGORITHM_H
#include"data_structure.h"
#include<iostream>

#define MaxIteration 100
class FM {
public:
	void one_swap(Bucket& bu, POINTER_ARRAY& pointer_array_local, POINTER_ARRAY& pointer_array_global, int currentBest);
	std::vector<std::vector<int>> FM_Algorithm(std::vector<std::vector<int>>& modules);
	std::vector<std::vector<int>> FM_Algorithm_Pertubation(std::vector<std::vector<int>>& modules);
	int mincutsize;
};


#endif