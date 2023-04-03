#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"
#include "Control.h"

namespace dynamicArray {
	extern Function create, update;
	extern Button grow;
	extern std::vector<int> arr;
	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}