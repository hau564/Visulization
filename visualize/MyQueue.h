#pragma once

#include "Node.h"

class MyQueue {
public:
	Node* head, *tail;
	int n = 0;

	MyQueue() {
		n = 0;
		head = tail = nullptr;
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
		Node* temp = new Node{ x };
		if (tail) tail = tail->next = temp;
		else tail = head = temp;
		++n;
	}
	void pop_front() {
		if (head) {
			--n;
			Node* temp = head;
			head = head->next;
			if (head == nullptr) tail = nullptr;
			delete temp;
		}
	}
	void clear() {
		while (head) pop_front();
	}
};