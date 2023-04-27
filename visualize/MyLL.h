#pragma once

#include "Node.h"
#include<vector>

class MyLL {
public:
	Node* head;
	int n = 0;

	MyLL() {
		n = 0;
		head = nullptr;
	}

	int size();
	bool empty();
	std::vector<int> getValues();

	void del(int pos);
	void ins(int pos, int x);
	void upd(int pos, int val);
	void clear();
};