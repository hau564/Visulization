#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include "Button.h"

class Textbox {
public:
	sf::Font font;
	sf::Text guideText, text;
	std::string inputString = "", charSet;
	sf::FloatRect box;
	Button buttonText;
	int isActive = 0, lengthLimit, textLengthLimit;

	Textbox() {};
	void create(sf::Vector2f pos, sf::Vector2f size, std::string textStr, int _lengthLimit = 1000000000, std::string charSet = "", int charSize = 0);
	void run(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);
	void clear();
	void applyText();
};