#pragma once

#include<SFML/Graphics.hpp>
#include "DropdownBox.h"

class Taskbar {
public:
	Taskbar() {};
	void create(sf::Vector2f pos, sf::Vector2f blockSize, sf::Vector2f dropSize, Button4Faces blockStyle, Button4Faces dropStyle, const std::vector<std::vector<std::string>> strings);
	std::string run(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);

private:
	bool anyDropped;
	std::vector<DropdownBox> dropdownBoxes;
};