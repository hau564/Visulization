#pragma once

#include<SFML/Graphics.hpp>

class LinkedListNode {
public:
	LinkedListNode() {};
	LinkedListNode(sf::Vector2f pos, int x);

	void create(sf::Vector2f pos, int x);
	void setColor(sf::Color color);
	void draw(sf::RenderWindow& window);

	void beNormal();
	void beTarget();
	void beVisited();

	sf::Vector2f getPosition();

	sf::CircleShape bound;
	sf::Text text;
};
