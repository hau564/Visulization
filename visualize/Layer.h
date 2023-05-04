#pragma once

#include<SFML/Graphics.hpp>
#include "Arrow.h"
#include "ArrayNode.h"
#include "LinkedListNode.h"

class Layer {
public:
	std::vector<ArrayNode> arr;
	std::vector<LinkedListNode> list;
	std::vector<Arrow> arrow;
	std::vector<sf::Text> text;
	int up = 100;

	void addArray(std::vector<int> a, sf::Vector2f pos = { 0, 0 }, int cap = -1);
	void addLinkedList(std::vector<int> llist, sf::Vector2f pos = { 0, 0 });
	void addDLinkedList(std::vector<int> llist, sf::Vector2f pos = { 0, 0 });
	void addCLinkedList(std::vector<int> llist, sf::Vector2f pos = { 0, 0 });
	void addArrow(sf::Vector2f pos1, sf::Vector2f pos2);
	void addTextAbove(std::string s, sf::Vector2f pos, sf::Vector2f displace);
	
	void addTextAbove(std::string s, LinkedListNode node, sf::Vector2f displace);
	void addTextAbove(std::string s, ArrayNode node, sf::Vector2f displace);
	
	template<class Obj1, class Obj2>
	void addArrow(Obj1 o1, Obj2 o2);

	void draw(sf::RenderWindow& window);
	void clear();
};

template<class Obj1, class Obj2>
inline void Layer::addArrow(Obj1 o1, Obj2 o2)
{
	arrow.push_back(Arrow(o1, o2));
}
