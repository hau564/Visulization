#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include "Button.h"

class Taskbar {
public:
	void create(sf::Vector2f pos, sf::Vector2f size, Button4Faces style, std::vector<std::string> labels, int _w = 0, int charSize = 0);
	std::string run(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);

	enum DirId { right = 0, up = 1, left = 2, down = 3 };
	int dir[5] = { 1, 0, -1, 0, 1 };
	int w;
	std::vector<Button> buttons;
};
