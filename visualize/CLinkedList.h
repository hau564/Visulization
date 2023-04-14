#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"

namespace circularLinkedList {
	extern std::vector<int> list;
	extern Function create, update, del, insert, search;

	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}