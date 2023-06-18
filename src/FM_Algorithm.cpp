#include"FM_Algorithm.h"
#include<limits>
void FM::one_swap(Bucket& bu,POINTER_ARRAY& pointer_array_local,POINTER_ARRAY& pointer_array_global,int currentBest) {
	int record = std::numeric_limits<int>::max();
	for (int loop = 0;loop < pointer_array_local.data_array.size() / 2;loop++) {
		int Areplace, Breplace;
		//select a vertex with maximal gain in A
		Areplace = bu.maxGain(A_PART, pointer_array_local);
		//move to B
		pointer_array_local.data_array[Areplace]->lockedstate = LOCKED;
		pointer_array_local.data_array[Areplace]->Node_Partition = B_PART;
		//update gains
		int prevGain, updateGain;
		prevGain = pointer_array_local.data_array[Areplace]->nodeGain;
		updateGain = pointer_array_local.updateGain(Areplace);
		bu.updateExchange(A_PART, Areplace, updateGain, prevGain);
		for (int i = 0;i < pointer_array_local.data_array[Areplace]->ConnectedNode.size();i++) {
			prevGain = pointer_array_local.data_array[pointer_array_local.data_array[Areplace]->ConnectedNode[i]]->nodeGain;
			updateGain = pointer_array_local.updateGain(pointer_array_local.data_array[Areplace]->ConnectedNode[i]);
			bu.updateLocal(pointer_array_local.data_array[pointer_array_local.data_array[Areplace]->ConnectedNode[i]]->Node_Partition, pointer_array_local.data_array[Areplace]->ConnectedNode[i], updateGain, prevGain);
		}

		//select a vertex with maximal gain in B
		Breplace = bu.maxGain(B_PART, pointer_array_local);
		//move to A
		pointer_array_local.data_array[Breplace]->lockedstate = LOCKED;
		pointer_array_local.data_array[Breplace]->Node_Partition = A_PART;
		//update gains
		prevGain = pointer_array_local.data_array[Breplace]->nodeGain;
		updateGain = pointer_array_local.updateGain(Breplace);
		bu.updateExchange(B_PART, Breplace, updateGain, prevGain);
		for (int i = 0;i < pointer_array_local.data_array[Breplace]->ConnectedNode.size();i++) {
			prevGain = pointer_array_local.data_array[pointer_array_local.data_array[Breplace]->ConnectedNode[i]]->nodeGain;
			updateGain = pointer_array_local.updateGain(pointer_array_local.data_array[Breplace]->ConnectedNode[i]);
			bu.updateLocal(pointer_array_local.data_array[pointer_array_local.data_array[Breplace]->ConnectedNode[i]]->Node_Partition, pointer_array_local.data_array[Breplace]->ConnectedNode[i], updateGain, prevGain);
		}
		//record the gain
		if (pointer_array_local.cutSize() < record&& pointer_array_local.cutSize()<currentBest) {
			record = pointer_array_local.cutSize();
			pointer_array_global.reset(pointer_array_local);
		}
	}
	pointer_array_global.recover();

}

std::vector<std::vector<int>> FM::FM_Algorithm(std::vector<std::vector<int>>& modules) {
	std::vector<std::vector<int>> partition;
	std::vector<int> tpA;
	std::vector<int> tpB;
	POINTER_ARRAY pointer_array_global(modules);              //�����ļ�����
	int currentBest = std::numeric_limits<int>::max();
	//������ֻ��ڵ㣬ȷ����ʼ�ָ��
//	pointer_array_global.init_half();
	pointer_array_global.init_even();
	pointer_array_global.updateGain();
	//ѭ������FM�㷨
	for (int loop = 0;loop < MaxIteration;loop++) {
		int flag = 0;
		Bucket bu;
		POINTER_ARRAY pointer_array_local;
		pointer_array_local.copy(pointer_array_global);
		//��ʼ��Ͱ�ṹ
		bu.load(pointer_array_local);
		one_swap(bu, pointer_array_local, pointer_array_global,currentBest);
		if (currentBest > pointer_array_global.cutSize()) {
			currentBest = pointer_array_global.cutSize();
			flag = 1;
		}
		std::cout << "iteration " << loop << ": Cut Size = " << pointer_array_global.cutSize() << std::endl;
		for (int i = 0;i < pointer_array_local.data_array.size();i++) {
			free(pointer_array_local.data_array[i]);
		}
		if (flag == 0) {
			break;
		}
	}

	std::cout << "FM algorithm done. " << "Cut Size = " << pointer_array_global.cutSize() << std::endl;
	std::cout << "Partition Result: "<<std::endl;
	std::cout << "A Part: ";
	for (int i = 0;i < pointer_array_global.data_array.size();i++) {
		if (pointer_array_global.data_array[i]->Node_Partition == A_PART) {
			std::cout << pointer_array_global.data_array[i]->nodeIndex<<" ";
			tpA.push_back(pointer_array_global.data_array[i]->nodeIndex);
		}
	}
	std::cout << std::endl;
	std::cout << "B Part: ";
	for (int i = 0;i < pointer_array_global.data_array.size();i++) {
		if (pointer_array_global.data_array[i]->Node_Partition == B_PART) {
			std::cout << pointer_array_global.data_array[i]->nodeIndex<<" ";
			tpB.push_back(pointer_array_global.data_array[i]->nodeIndex);
		}
	}
	partition.push_back(tpA);
	partition.push_back(tpB);
	mincutsize = currentBest;
	return partition;
}

std::vector<std::vector<int>> FM::FM_Algorithm_Pertubation(std::vector<std::vector<int>> &modules) {
	int min_cut_size = std::numeric_limits<int>::max();
	std::vector<std::vector<int>> partition;
	std::vector<int> tpA;
	std::vector<int> tpB;
	for (int l = 0;l < 5;l++) {
		POINTER_ARRAY pointer_array_global(modules);              //�����ļ�����

		std::cout << "FM " << l << std::endl;
		int currentBest = std::numeric_limits<int>::max();
		//������ֻ��ڵ㣬ȷ����ʼ�ָ��
		pointer_array_global.init_rand();
		pointer_array_global.updateGain();
		//ѭ������FM�㷨
		for (int loop = 0;loop < MaxIteration;loop++) {
			int flag = 0;
			Bucket bu;
			POINTER_ARRAY pointer_array_local;
			pointer_array_local.copy(pointer_array_global);
			//��ʼ��Ͱ�ṹ
			bu.load(pointer_array_local);
			one_swap(bu, pointer_array_local, pointer_array_global, currentBest);
			if (currentBest > pointer_array_global.cutSize()) {
				currentBest = pointer_array_global.cutSize();
				flag = 1;
			}
			std::cout << "iteration " << loop << ": Cut Size = " << pointer_array_global.cutSize() << std::endl;
			for (int i = 0;i < pointer_array_local.data_array.size();i++) {
				free(pointer_array_local.data_array[i]);
			}
			if (flag == 0) {
				break;
			}
		}

		std::cout << "FM algorithm " << l << " done. " << "Cut Size = " << pointer_array_global.cutSize() << std::endl;
		std::cout << "Partition Result: " << std::endl;
		std::cout << "A Part: ";
		for (int i = 0;i < pointer_array_global.data_array.size();i++) {
			if (pointer_array_global.data_array[i]->Node_Partition == A_PART) {
				std::cout << pointer_array_global.data_array[i]->nodeIndex << " ";
			}
		}
		std::cout << std::endl;
		std::cout << "B Part: ";
		for (int i = 0;i < pointer_array_global.data_array.size();i++) {
			if (pointer_array_global.data_array[i]->Node_Partition == B_PART) {
				std::cout << pointer_array_global.data_array[i]->nodeIndex << " ";
			}
		}
		if (min_cut_size > pointer_array_global.cutSize()) {
			min_cut_size = pointer_array_global.cutSize();
			tpA.clear();
			tpB.clear();
			for (int i = 0;i < pointer_array_global.data_array.size();i++) {
				if (pointer_array_global.data_array[i]->Node_Partition == A_PART) {
					tpA.push_back(pointer_array_global.data_array[i]->nodeIndex);
				}
			}
			for (int i = 0;i < pointer_array_global.data_array.size();i++) {
				if (pointer_array_global.data_array[i]->Node_Partition == B_PART) {
					tpB.push_back(pointer_array_global.data_array[i]->nodeIndex);
				}
			}
			
		}
		std::cout << std::endl;
	}
	partition.push_back(tpA);
	partition.push_back(tpB);
	std::cout << "The Best Partition Result: Cut Size =  " << min_cut_size << std::endl;
	mincutsize = min_cut_size;
	return partition;
}