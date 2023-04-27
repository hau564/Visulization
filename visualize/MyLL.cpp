#include "MyLL.h"
#include<iostream>

int MyLL::size() {
	return n;
}
bool MyLL::empty() {
	return (!n);
}

std::vector<int> MyLL::getValues()
{
	Node* cur = head;
	std::vector<int> a;
	while (cur) {
		a.push_back(cur->val);
		cur = cur->next;
	}
	return a;
}

void MyLL::del(int pos)
{
	if (pos < 0 || pos >= n) return;
	if (!pos) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	else {
		Node* cur = head;
		for (int i = 1; i < pos; ++i) cur = cur->next;
		Node* temp = cur->next;
		cur->next = cur->next->next;
		delete temp;
	}
	--n;
}

void MyLL::ins(int pos, int x)
{
	if (pos < 0 || pos > n) return;
	if (!pos) {
		Node* temp = new Node{ x, head };
		head = temp;
	}
	else {
		Node* cur = head;
		for (int i = 1; i < pos; ++i) cur = cur->next;
		Node* temp = new Node{ x, cur->next };
		cur->next = temp;
	}
	++n;
}

void MyLL::upd(int pos, int val)
{
	if (pos < 0 || pos >= n) return;
	Node* cur = head;
	for (int i = 1; i <= pos; ++i) cur = cur->next;
	cur->val = val;
}

void MyLL::clear()
{
	while (head) del(0);
}
