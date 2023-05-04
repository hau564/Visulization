#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"
#include "Control.h"

namespace dynamicArray {
	extern Function create, access, update, del, insert, search, grow, shrink;
	extern int cap;
	extern std::vector<int> arr;
	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}