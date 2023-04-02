#pragma once

#include<SFML/Graphics.hpp>

class Slider {
public:
	int selectedLength;
	sf::RectangleShape background, selected;
	sf::Vector2f pos, size;
	int cntDiv, lenDiv;
	int holding = 0;

	void create(sf::Vector2f pos, sf::Vector2f size, sf::Color backColor, sf::Color seleColor, float initialRate = 0, int _cntDiv = 10);
	float run(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);
	void add(int x);
	void setSelected(float x);
	void round(float x);

	float get();
};