#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"

namespace stack {
	extern std::vector<int> list;
	extern Function create, push, pop, peek;

	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}