#pragma once

#include<SFML/Graphics.hpp>
#include "Function.h"
#include "MyStack.h"

namespace stack {
	extern MyStack list;
	extern Function create, push, pop, peek, clear;

	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}