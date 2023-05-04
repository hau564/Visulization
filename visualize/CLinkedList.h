#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"
#include "MyLL.h"

namespace circularLinkedList {
	extern MyLL list;
	extern Function create, update, del, insert, search;

	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}