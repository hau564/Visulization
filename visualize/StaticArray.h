#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"

namespace staticArray {
	extern std::vector<Function> functions;
	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}