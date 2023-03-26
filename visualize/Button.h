#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class ButtonFace {
public:
	float outlineThickness;

	sf::Color backgroundColor;
	sf::Color outlineColor;
	
	sf::RectangleShape create(sf::Vector2f pos, sf::Vector2f size);
};



class Button4Faces {
public:
	ButtonFace normal, focused, pressed, disabled;
};



class Button {
public:
	Button() {};
	void create(const sf::Vector2f pos, sf::Vector2f size, Button4Faces states, const std::string strText, int _mode = 0, int charSize = 0);
	int run(sf::RenderWindow &window, sf::Event event);
	const void draw(sf::RenderWindow& window) const;

	bool isPressed();
	bool isFocused();
	void resetState();
	std::string getLabel();
	
	enum StateId {normal = 0, focused = 1, pressed = 2, disabled = 3};
	enum Mode {NormalMode = 0, OnOffMode = 1, AutoOff = 2, StayClick = 3};

	int state = normal, mode = NormalMode; 
	sf::RectangleShape faces[4];
	sf::Text text;
	sf::Vector2f pos, size;

	sf::Font font;
};