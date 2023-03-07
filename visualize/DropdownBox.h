#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

class DropdownBox {
public:
	DropdownBox() {};
	void create(sf::Vector2f pos, sf::Vector2f labelButtonSize, sf::Vector2f blockSize, Button4Faces blockStyle, const std::vector<std::string> labelStr);
	std::string run(sf::RenderWindow &window, sf::Event event);
	void disDropped();
	void onDropped();

	bool dropped = false;
	std::vector<Button> droppedButtons;
	Button labelButton;
	void draw(sf::RenderWindow& window);
};