#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include<vector>
#include<algorithm>
#include<map>
#include<utility>
#include<ctime>
#include<random>

typedef enum {
	NO_PART = -1,
	A_PART = 0,
	B_PART = 1
}NODE_PART;

typedef enum {
	UNLOCKED = 0,
	LOCKED = 1
}LOCK_STATE;


//NODE class

class NODE {
public:
	int nodeIndex;
	NODE_PART Node_Partition;
	LOCK_STATE lockedstate;
	int nodeGain;
	std::vector<int> ConnectedNode;

	NODE() {
		nodeIndex = -1;
		Node_Partition = NO_PART;
		lockedstate = UNLOCKED;
		nodeGain = 0;
		ConnectedNode.clear();
	}
	NODE(int i, std::vector<int> connect) {
		nodeIndex = i;
		Node_Partition = NO_PART;
		lockedstate = UNLOCKED;
		nodeGain = 0;
		ConnectedNode.assign(connect.begin(),connect.end());
	}
	NODE(int i,NODE_PART partition,LOCK_STATE ls,int gain,std::vector<int> connect) {
		nodeIndex = i;
		Node_Partition = partition;
		lockedstate = ls;
		nodeGain = gain;
		ConnectedNode.assign(connect.begin(), connect.end());
	}

};

class POINTER_ARRAY {
public:
	std::vector<NODE*> data_array;

	POINTER_ARRAY() {
	}
	POINTER_ARRAY(std::vector<std::vector<int>>& modules) {
		for (int i = 0;i < modules.size();i++) {
			data_array.push_back(new NODE(i, modules[i]));
		}
	}
	void copy(POINTER_ARRAY pa) {
		for (int i = 0;i < pa.data_array.size();i++) {
			this->data_array.push_back(new NODE(i, pa.data_array[i]->Node_Partition, pa.data_array[i]->lockedstate, pa.data_array[i]->nodeGain, pa.data_array[i]->ConnectedNode));
		}
	}
	void reset(POINTER_ARRAY pa) {
		for (int i = 0;i < pa.data_array.size();i++) {
			data_array[i]->lockedstate = pa.data_array[i]->lockedstate;
			data_array[i]->nodeGain = pa.data_array[i]->nodeIndex;
			data_array[i]->Node_Partition = pa.data_array[i]->Node_Partition;
		}
	}
	void recover() {
		for (int i = 0;i < data_array.size();i++) {
			data_array[i]->lockedstate = UNLOCKED;
		}
	}
	void init_half() {
		for (int i = 0;i < data_array.size() / 2;i++) {
			data_array[i]->Node_Partition = A_PART;
		}
		for (int i = data_array.size() / 2;i < data_array.size();i++) {
			data_array[i]->Node_Partition = B_PART;
		}
	}
	void init_even() {
		for (int i = 0;i < data_array.size();i++) {
			if (i % 2 == 0) {
				data_array[i]->Node_Partition = A_PART;
			}
			else if (i % 2 == 1) {
				data_array[i]->Node_Partition = B_PART;
			}
		}
	}
	void init_rand() {
		int a_num = 0;
		int b_num = 0;
		std::default_random_engine rd;
		std::uniform_int_distribution<int> u(0, 1);
		rd.seed(time(0));
		for (int i = 0;i < data_array.size();i++) {
			if (a_num == 1000) {
				data_array[i]->Node_Partition = B_PART;
			}
			else if (b_num == 1000) {
				data_array[i]->Node_Partition = A_PART;
			}
			else if (u(rd) == 0) {
				data_array[i]->Node_Partition = A_PART;
				a_num++;
			}
			else{
				data_array[i]->Node_Partition = B_PART;
				b_num++;
			}
		}
	}
	void updateGain() {
		for (int i = 0;i < data_array.size();i++) {
			int internal = 0;
			int external = 0;
			int record = data_array[i]->Node_Partition;
			for (auto iter = data_array[i]->ConnectedNode.begin();iter != data_array[i]->ConnectedNode.end();iter++) {
				if (data_array[(*iter)]->Node_Partition == record && record != -1) {
					internal++;
				}
				else if (data_array[(*iter)]->Node_Partition == 1 - record) {
					external++;
				}
			}
			data_array[i]->nodeGain = external - internal;
		}
	}
	int updateGain(int i) {
		int internal = 0;
		int external = 0;
		int record = data_array[i]->Node_Partition;
		for (auto iter = data_array[i]->ConnectedNode.begin();iter != data_array[i]->ConnectedNode.end();iter++) {
			if (data_array[(*iter)]->Node_Partition == record && record != -1) {
				internal++;
			}
			else if (data_array[(*iter)]->Node_Partition == 1 - record) {
				external++;
			}
		}
		data_array[i]->nodeGain = external - internal;
		return data_array[i]->nodeGain;
	}
	int cutSize() {
		int cutsize = 0;
		for (int i = 0;i < data_array.size();i++) {
			if (data_array[i]->Node_Partition == A_PART) {
				for (auto iter = data_array[i]->ConnectedNode.begin();iter != data_array[i]->ConnectedNode.end();iter++) {
					if (data_array[(*iter)]->Node_Partition != data_array[i]->Node_Partition) {
						cutsize++;
					}
				}
			}
		}
		return cutsize;
	}
};

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

	Bucket() {

	}
	void load(POINTER_ARRAY& parr) {
		for (int i = 0;i < parr.data_array.size();i++) {
			if (parr.data_array[i]->Node_Partition == A_PART) {
				auto iter = bucketAtoB.find(parr.data_array[i]->nodeGain);
				if (iter != bucketAtoB.end()) {
					BucketNode* temp = iter->second;
					BucketNode* insert = iter->second;
					for (temp = iter->second;temp != NULL;temp = temp->next) {
						insert = temp;
					}
					insert->next = new BucketNode(parr.data_array[i]->nodeIndex, NULL, insert);
				}
				else if (iter == bucketAtoB.end()) {
					BucketNode* head = new BucketNode(-1, NULL, NULL);
					bucketAtoB.insert(std::pair<int, BucketNode*>(parr.data_array[i]->nodeGain, head));
					head->next = new BucketNode(parr.data_array[i]->nodeIndex, NULL, head);
				}
			}
			if (parr.data_array[i]->Node_Partition == B_PART) {
				auto iter = bucketBtoA.find(parr.data_array[i]->nodeGain);
				if (iter != bucketBtoA.end()) {
					BucketNode* temp = iter->second;
					BucketNode* insert = iter->second;
					for (temp = iter->second;temp != NULL;temp = temp->next) {
						insert = temp;
					}
					insert->next = new BucketNode(parr.data_array[i]->nodeIndex, NULL, insert);
				}
				else if (iter == bucketBtoA.end()) {
					BucketNode* head = new BucketNode(-1, NULL, NULL);
					bucketBtoA.insert(std::pair<int, BucketNode*>(parr.data_array[i]->nodeGain, head));
					head->next = new BucketNode(parr.data_array[i]->nodeIndex, NULL, head);
				}
			}
		}
	}
	int maxGain(NODE_PART partition,POINTER_ARRAY& parr) {
		if (partition == A_PART) {
			for (auto iter = bucketAtoB.begin();iter != bucketAtoB.end();iter++) {
				BucketNode* temp;
				for (temp = iter->second;temp != NULL;temp = temp->next) {
					if (temp->nodeIndex > -1) {
						if (parr.data_array[temp->nodeIndex]->lockedstate == UNLOCKED) {
							return temp->nodeIndex;
						}
					}
				}
			}
		}
		else if (partition == B_PART) {
			for (auto iter = bucketBtoA.begin();iter != bucketBtoA.end();iter++) {
				BucketNode* temp;
				for (temp = iter->second;temp != NULL;temp = temp->next) {
					if (temp->nodeIndex > -1) {
						if (parr.data_array[temp->nodeIndex]->lockedstate == UNLOCKED) {
							return temp->nodeIndex;
						}
					}
				}
			}
		}
	}
	void updateExchange(NODE_PART partition, int i, int updateGain,int prevGain) {
		if (partition == A_PART) {
			auto iter = bucketAtoB.find(prevGain);
			BucketNode* temp = iter->second;
			for (temp = iter->second;temp != NULL;temp = temp->next) {
				if (temp->nodeIndex == i) {
					break;
				}
			}
			if (temp->next == NULL) {
				//delete temp from bucket A
				temp->prev->next = temp->next;
				temp->prev = NULL;
			}
			else if (temp->next != NULL) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next = NULL;
				temp->prev = NULL;
			}
			//add temp to bucket B
			auto iter0 = bucketBtoA.find(updateGain);
				if (iter0 != bucketBtoA.end()) {
					BucketNode* temp0 = iter0->second;
					BucketNode* insert0 = iter0->second;
					for (temp0 = iter0->second;temp0 != NULL;temp0 = temp0->next) {
						insert0 = temp0;
					}
					insert0->next = temp;
					temp->prev = insert0;
				}
				else if (iter0 == bucketBtoA.end()) {
					BucketNode* head = new BucketNode(-1, NULL, NULL);
					bucketBtoA.insert(std::pair<int, BucketNode*>(updateGain, head));
					head->next = temp;
					temp->prev = head;
				}
		}
		else if (partition == B_PART) {
			auto iter = bucketBtoA.find(prevGain);
			BucketNode* temp = iter->second;
			for (temp = iter->second;temp != NULL;temp = temp->next) {
				if (temp->nodeIndex == i) {
					break;
				}
			}
			if (temp->next == NULL) {
				//delete temp from bucket B
				temp->prev->next = temp->next;
				temp->prev = NULL;
			}
			else if (temp->next != NULL) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next = NULL;
				temp->prev = NULL;
			}
			//add temp to bucket A
			auto iter0 = bucketAtoB.find(updateGain);
			if (iter0 != bucketAtoB.end()) {
				BucketNode* temp0 = iter0->second;
				BucketNode* insert0 = iter0->second;
				for (temp0 = iter0->second;temp0 != NULL;temp0 = temp0->next) {
					insert0 = temp0;
				}
				insert0->next = temp;
				temp->prev = insert0;
			}
			else if (iter0 == bucketAtoB.end()) {
				BucketNode* head = new BucketNode(-1, NULL, NULL);
				bucketAtoB.insert(std::pair<int, BucketNode*>(updateGain, head));
				head->next = temp;
				temp->prev = head;
			}
		}
	}
	void updateLocal(NODE_PART partition, int i, int updateGain, int prevGain) {
		if (partition == A_PART) {
			auto iter = bucketAtoB.find(prevGain);
			BucketNode* temp = iter->second;
			for (temp = iter->second;temp != NULL;temp = temp->next) {
				if (temp->nodeIndex == i) {
					break;
				}
			}
			if (temp->next == NULL) {
				//delete temp from bucket A
				temp->prev->next = temp->next;
				temp->prev = NULL;
			}
			else if (temp->next != NULL) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next = NULL;
				temp->prev = NULL;
			}
			//add temp to bucket A
			auto iter0 = bucketAtoB.find(updateGain);
			if (iter0 != bucketAtoB.end()) {
				BucketNode* temp0 = iter0->second;
				BucketNode* insert0 = iter0->second;
				for (temp0 = iter0->second;temp0 != NULL;temp0 = temp0->next) {
					insert0 = temp0;
				}
				insert0->next = temp;
				temp->prev = insert0;
			}
			else if (iter0 == bucketAtoB.end()) {
				BucketNode* head = new BucketNode(-1, NULL, NULL);
				bucketAtoB.insert(std::pair<int, BucketNode*>(updateGain, head));
				head->next = temp;
				temp->prev = head;
			}
		}
		else if (partition == B_PART) {
			auto iter = bucketBtoA.find(prevGain);
			BucketNode* temp = iter->second;
			for (temp = iter->second;temp != NULL;temp = temp->next) {
				if (temp->nodeIndex == i) {
					break;
				}
			}
			if (temp->next == NULL) {
				//delete temp from bucket B
				temp->prev->next = temp->next;
				temp->prev = NULL;
			}
			else if (temp->next != NULL) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next = NULL;
				temp->prev = NULL;
			}
			//add temp to bucket B
			auto iter0 = bucketBtoA.find(updateGain);
			if (iter0 != bucketBtoA.end()) {
				BucketNode* temp0 = iter0->second;
				BucketNode* insert0 = iter0->second;
				for (temp0 = iter0->second;temp0 != NULL;temp0 = temp0->next) {
					insert0 = temp0;
				}
				insert0->next = temp;
				temp->prev = insert0;
			}
			else if (iter0 == bucketBtoA.end()) {
				BucketNode* head = new BucketNode(-1, NULL, NULL);
				bucketBtoA.insert(std::pair<int, BucketNode*>(updateGain, head));
				head->next = temp;
				temp->prev = head;
			}
		}
	}
};































#endif

