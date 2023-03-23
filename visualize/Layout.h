#pragma once

#include "Style.h"
#include "Taskbar.h"
#include<SFML/Graphics.hpp>

namespace layout {
	extern int Width, Height;

	namespace functionWindow {
		extern sf::Vector2f size;
		extern sf::Vector2f pos;
		extern sf::Vector2f blockSize;

		extern sf::RectangleShape shape;
	}

	namespace sourceWindow {
		extern sf::Vector2f size;
		extern sf::Vector2f pos;
		extern sf::Vector2f blockSize;

		extern sf::RectangleShape shape;
	}

	namespace structuresBar {
		extern std::vector<std::string> labels;
	
		extern sf::Vector2f pos;
		extern sf::Vector2f blockSize;
		extern int direction;
		extern int charSize;

		extern Taskbar bar;
	}

	extern void init();
}