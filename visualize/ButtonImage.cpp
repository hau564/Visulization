#include "ButtonImage.h"
#include "MousePos.h"
#include "Style.h"

void ButtonImage::create(sf::Vector2f _pos, sf::Vector2f _size, const std::vector<std::string> addresses, int _mode)
{
	pos = _pos, size = _size;
	int _m = (int)addresses.size();
	for (int i = 0; i < 3; ++i) {
		texts[i].loadFromFile(addresses[std::min(i, _m - 1)]);
		
		faces[i].setTexture(texts[i]);
		faces[i].setPosition(pos);

		sf::Vector2f tSize = (sf::Vector2f)texts[i].getSize();
		faces[i].setScale(sf::Vector2f(size.x / tSize.x, size.y / tSize.y));
		
	}
	sf::Color col = style::backgroundColor;
	if (col.r + col.g + col.b <= 100) {
		col.r = std::min(255, col.r + 50);
		col.g = std::min(255, col.g + 50);
		col.b = std::min(255, col.b + 50);
	}
	bound.setPosition(pos);
	bound.setSize(size);
	bound.setFillColor(col);

	state = normal;
	mode = _mode;
}

int ButtonImage::run(sf::RenderWindow& window, sf::Event event) {
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

void ButtonImage::draw(sf::RenderWindow& window) {
	window.draw(bound);
	window.draw(faces[state]);
}

void ButtonImage::resetState() {
	state = normal;
}

bool ButtonImage::isPressed() {
	return state == pressed;
}
bool ButtonImage::justPressed() {
	return prevState != pressed && state == pressed;
}
bool ButtonImage::isFocused() {
	return state == focused;
}