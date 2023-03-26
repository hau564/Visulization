#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace display {
	extern std::vector<sf::Text> texts;
	extern std::vector<sf::CircleShape> circles;
	extern std::vector<sf::RectangleShape> rectangles;

	extern void clear();
	extern void createArray(std::string _n, std::string _values);
	extern void displayAll();
}