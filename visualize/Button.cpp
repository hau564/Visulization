#pragma once

#include "Button.h"
#include "MousePos.h"


sf::RectangleShape ButtonFace::create(sf::Vector2f pos, sf::Vector2f size) {
	sf::RectangleShape rect;

	rect.setSize(size);
	rect.setPosition(pos);

	rect.setFillColor(ButtonFace::backgroundColor);
	rect.setOutlineColor(ButtonFace::outlineColor);
	rect.setOutlineThickness(ButtonFace::outlineThickness);

	return rect;
}



void Button::create(sf::Vector2f _pos, sf::Vector2f _size, Button4Faces state, const std::string label, int _mode, int charSize) {
	pos = _pos, size = _size;
	Button::faces[0] = state.normal.create(pos, size);
	Button::faces[1] = state.focused.create(pos, size);
	Button::faces[2] = state.pressed.create(pos, size);
	Button::faces[3] = state.disabled.create(pos, size);


	mode = _mode;


	Button::font.loadFromFile("font/arial.ttf");
	Button::text.setFont(font);
	Button::text.setString(label);
	Button::text.setCharacterSize(charSize ? charSize : (int)size.y / 2);

	sf::FloatRect textRect = text.getLocalBounds();
	Button::text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	Button::text.setPosition(sf::Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));
	Button::text.setFillColor(sf::Color::Black);


	//std::cout << "Button created successfull at " << pos.x << " " << pos.y << ": " << label << std::endl;
}

int Button::run(sf::RenderWindow& window, sf::Event event) {
	prevState = state;

	sf::FloatRect buttonBounds(pos, size);
	sf::Vector2f mousePos = (sf::Vector2f)getMousePos(window);
	if (mode == NormalMode) {
		if (buttonBounds.contains(mousePos.x, mousePos.y))
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
			state = normal;
		}
	}

	if (mode != NormalMode) {
		if (buttonBounds.contains(mousePos.x, mousePos.y))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (state != pressed) state = pressed;
				else if (mode != StayClick) state = focused;
			}
			else if (state != pressed) state = focused;
		}
		else {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				if (mode == AutoOff || mode == StayClick) state = normal;
			if (state == focused) state = normal;
		}
	}

	return state;
}

const void Button::draw(sf::RenderWindow& window) const {
	window.draw(Button::faces[state]);
	window.draw(Button::text);
}

void Button::resetState() {
	state = normal;
}

bool Button::isPressed() {
	return state == pressed;
}
bool Button::justPressed() {
	return prevState != pressed && state == pressed;
}
bool Button::isFocused() {
	return state == focused;
}

std::string Button::getLabel() {
	return text.getString().toAnsiString();
}