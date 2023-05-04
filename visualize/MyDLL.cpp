#include "MyDLL.h"
#include<iostream>

int MyDLL::size() {
	return n;
}
bool MyDLL::empty() {
	return (!n);
}

std::vector<int> MyDLL::getValues()
{
	Node* cur = head;
	std::vector<int> a;
	while (cur) {
		a.push_back(cur->val);
		cur = cur->next;
	}
	return a;
}

void MyDLL::del(int pos)
{
	if (pos < 0 || pos >= n) return;
	if (!pos) {
		Node* temp = head;
		head = head->next;
		if (head) head->prev = nullptr;
		delete temp;
	}
	else {
		Node* cur = head;
		for (int i = 1; i < pos; ++i) cur = cur->next;
		Node* temp = cur->next;
		cur->next = cur->next->next;
		if (cur->next)
			cur->next->prev = cur;
		delete temp;
	}
	--n;
}

void MyDLL::ins(int pos, int x)
{
	if (pos < 0 || pos > n) return;
	if (!pos) {
		Node* temp = new Node{ x, head, nullptr };
		head = temp;
	}
	else {
		Node* cur = head;
		for (int i = 1; i < pos; ++i) cur = cur->next;
		Node* temp = new Node{ x, cur->next, cur };
		if (cur->next) 
			cur->next->prev = temp;
		cur->next = temp;
	}
	++n;
}

void MyDLL::upd(int pos, int val)
{
	if (pos < 0 || pos >= n) return;
	Node* cur = head;
	for (int i = 1; i <= pos; ++i) cur = cur->next;
	cur->val = val;
}

void MyDLL::clear()
{
	while (head) del(0);
}
