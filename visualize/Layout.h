#pragma once

#include "Button.h"
#include "Style.h"
#include "Taskbar.h"
#include<SFML/Graphics.hpp>

namespace layout {
	int Width = 1920, Height = 1080;

	namespace functionWindow {
		sf::Vector2f size(300, 800);
		sf::Vector2f pos(Width - size.x, Height - size.y);

		sf::Vector2f blockSize(300, 100);
	}

	namespace structuresBar {
		std::vector<std::string> labels = { "Static Array", "Dyamic Array", "Linked List (LL)", "Doubly LL" , "Circular LL", "Queue", "Stack"};
	
		sf::Vector2f pos(0, 0);
		sf::Vector2f blockSize(Width / 7, 70);
		int direction = Taskbar::right;
		int charSize = 30;
	}
}