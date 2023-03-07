#pragma once

#include "Button.h"
#include "MousPos.h"

sf::RectangleShape ButtonFace::create(sf::Vector2f pos, sf::Vector2f size) {
	sf::RectangleShape rect;

	rect.setSize(size);
	rect.setPosition(pos);

	rect.setFillColor(ButtonFace::backgroundColor);
	rect.setOutlineColor(ButtonFace::outlineColor);
	rect.setOutlineThickness(ButtonFace::outlineThickness);

	return rect;
}



void Button::create(const sf::Vector2f pos, sf::Vector2f size, Button4Faces state, const std::string &strText, int textSize) {
	Button::faces[0] = state.normal.create(pos, size);
	Button::faces[1] = state.focused.create(pos, size);
	Button::faces[2] = state.pressed.create(pos, size);
	Button::faces[3] = state.disabled.create(pos, size);

	Button::font.loadFromFile("font/arial.ttf");
	
	Button::text.setFont(font);
	Button::text.setString(strText);
	Button::text.setCharacterSize(textSize ? textSize : (int)size.y);

	sf::FloatRect textRect = text.getLocalBounds();
	Button::text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	Button::text.setPosition(sf::Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));
	
	Button::text.setFillColor(sf::Color::Black);
}

void Button::resetState() {
	Button::state = 0;
}

int Button::run(sf::RenderWindow &window, sf::Event event) {
	sf::FloatRect buttonBounds(faces[0].getPosition(), faces[0].getSize());
	if (buttonBounds.contains(getMousePos(window).x, getMousePos(window).y))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			state = pressed;
		}
		else {
			if (state != pressed || event.type == sf::Event::MouseButtonReleased) state = focused;
		}
	}
	else {
		if (state != pressed || event.type == sf::Event::MouseButtonReleased) state = normal;
	}
	return state == pressed;
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(Button::faces[Button::state]);
	window.draw(Button::text);
}