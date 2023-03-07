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
	void create(const sf::Vector2f pos, sf::Vector2f size, Button4Faces states, const std::string strText, int textSize = 0);
	int run(sf::RenderWindow &window, sf::Event event);

	bool isPressed();
	bool isFocused();
	void resetState();
	std::string getLabel();
	
	enum StateId {normal = 0, focused = 1, pressed = 2, disabled = 3};

	const void draw(sf::RenderWindow& window) const;

	int state = normal; // 0 1 2 3 : normal focused pressed disabled
	sf::RectangleShape faces[4];
	sf::Text text;

	sf::Font font;
};