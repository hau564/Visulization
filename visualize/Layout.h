#pragma once

#include "Style.h"
#include "Taskbar.h"
#include<SFML/Graphics.hpp>

namespace layout {
	extern int Width, Height;
	extern sf::Font font;

	namespace controlWindow {
		extern sf::Vector2f size;
		extern sf::Vector2f pos;
		extern sf::RectangleShape shape;

		extern sf::Vector2f playPos, playSize;
		extern int dis;
		extern sf::Vector2f prevPos, prevSize;
		extern sf::Vector2f nextPos, nextSize;

		extern sf::Vector2f toStartPos, toStartSize;
		extern sf::Vector2f toEndPos, toEndSize;
	}

	namespace functionWindow {
		extern sf::Vector2f size;
		extern sf::Vector2f pos;
		extern sf::Vector2f blockSize;

		extern sf::RectangleShape shape;
	}

	namespace displayWindow {
		extern sf::Vector2f size;
		extern sf::Vector2f pos;
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

	namespace display {
		extern sf::Color normalColor, visitedColor, considerColor, targetColor;

		extern sf::Vector2f arrayBlockSize;
		extern sf::RectangleShape arrayBlock;
		extern sf::Text arrayText;
	}

	extern void init();
}