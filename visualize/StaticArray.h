#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"
#include "Textbox.h"

namespace staticArray {
	extern Button createButton, changeButton;
	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);

	extern int createActive;
	extern Textbox getSize, getValues;
	extern sf::RectangleShape createWindow;
	extern void Create(sf::RenderWindow& window, sf::Event event);
}