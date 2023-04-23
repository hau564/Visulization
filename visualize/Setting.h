#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include "Button.h"
#include "ButtonImage.h"

namespace setting {
	extern ButtonImage settingButton;
	extern std::vector<sf::Text> texts, colTexts;
	extern std::vector<sf::RectangleShape> rects;
	extern std::vector<sf::Color> colors;
	extern Button reset, dark, apply;

	extern void init();
	extern void draw(sf::RenderWindow& window);
	extern bool run(sf::RenderWindow& window, sf::Event& event);
}