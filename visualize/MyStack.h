#pragma once

#include "Node.h"

class MyStack {
public:
	Node* head;
	int n = 0;

	MyStack() {
		n = 0;
		head = nullptr;
	}

	int size() {
		return n;
	}
	bool empty() { return (!n); }
	std::vector<int> getValues() {
		Node* cur = head;
		std::vector<int> a;
		while (cur) {
			a.push_back(cur->val);
			cur = cur->next;
		}
		return a;
	}
	void push_back(int x) {

		Node* temp = new Node{ x, head };
		head = temp;
		++n;
	}
	void pop_back() {
		if (head) {
			--n;
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void clear() {
		while (head) pop_back();
	}
};