#pragma once

#include<SFML/Graphics.hpp>

class ButtonImage {
public:
	sf::Texture texts[4];
	sf::Sprite faces[4];
	sf::Vector2f pos, size;

	enum StateId {normal = 0, focused = 1, pressed = 2, disable = 3};
	enum Mode { NormalMode = 0, OnOffMode = 1, AutoOff = 2, StayClick = 3 };
	int state, mode;

	void create(sf::Vector2f _pos, sf::Vector2f _size, const std::vector<std::string> addresses, int _mode = NormalMode);
	int run(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);

	bool isPressed();
	bool isFocused();
	void resetState();
};