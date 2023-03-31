#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace display {
	extern std::vector<std::vector<sf::Text>> texts;
	extern std::vector<std::vector<sf::CircleShape>> circles;
	extern std::vector<std::vector<sf::RectangleShape>> rectangles;

	extern std::vector<int> arr;
	extern std::vector<int> ll;

	extern void clear();
	extern bool resetDisplay();

	extern void setTextRectangle(sf::Text& text, sf::RectangleShape& rect, std::string s);

	namespace array {
		extern void create(std::string _n, std::string _values);
		extern void create(std::vector<std::string> inputStrs);
		
		extern void update(std::string _pos, std::string _val);
		extern void update(std::vector<std::string> inputStrs);
	}

	extern void displayAll(sf::RenderWindow& window);
}