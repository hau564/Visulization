#pragma once

#include<SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include "Format.h"

namespace colorPicker {
	extern int Width, Height;
	extern std::vector<sf::RectangleShape> board, bar;
	
	extern Textbox rbox, gbox, bbox;
	extern sf::RectangleShape col;
	extern Button load;
		
	extern void init();
	extern sf::Color get(sf::Color defaultColor = sf::Color::White);
}