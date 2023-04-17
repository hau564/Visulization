#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include "Button.h"
#include "Textbox.h"

class Function {
public:
	Function() {};

	Button functionButton, go, file;
	std::vector<Textbox> textboxes;
	int active = 0;

	void create(sf::Vector2f pos, sf::Vector2f size, std::string label, std::vector<std::string> inputLabels);
	bool run(sf::RenderWindow& window, sf::Event event, std::vector<std::string> &get);
	void draw(sf::RenderWindow& window);
	std::vector<std::string> getInputVector();
};