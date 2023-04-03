#pragma once

#include<SFML/Graphics.hpp>

class ArrayNode {
public:
	ArrayNode() {};
	ArrayNode(sf::Vector2f pos, int x);

	void create(sf::Vector2f pos, int x);
	void setValue(int x);
	void setColor(sf::Color color);
	void draw(sf::RenderWindow& window);

	void beNormal();
	void beTarget();
	void beVisited();

	sf::Vector2f getPosition();

	sf::RectangleShape bound;
	sf::Text text;
};