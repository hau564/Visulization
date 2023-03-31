#include "Slider.h"
#include "MousePos.h"

void Slider::create(sf::Vector2f _pos, sf::Vector2f _size, sf::Color backColor, sf::Color seleColor, int initialLength, int _cntDiv) {
	pos = _pos, size = _size;
	
	background.setPosition(pos);
	background.setSize(size);
	background.setFillColor(backColor);
	background.setOutlineThickness(1);
	background.setOutlineColor(backColor);

	selectedLength = initialLength;
	selected.setPosition(pos);
	selected.setSize(sf::Vector2f(selectedLength, size.y));
	selected.setFillColor(seleColor);
	selected.setOutlineThickness(1);
	selected.setOutlineColor(seleColor);

	cntDiv = _cntDiv;
	lenDiv = size.x / cntDiv;
}

void Slider::add(int x) {
	selectedLength = std::max(0, std::min((int)size.x, selectedLength + x));
	selected.setSize(sf::Vector2f(selectedLength, size.y));
}

void Slider::setSelected(float x) {
	selectedLength = std::max(0.0f, std::min(size.x, x * size.x));
	selected.setSize(sf::Vector2f(selectedLength, size.y));
}

float Slider::run(sf::RenderWindow& window, sf::Event event) {
	sf::FloatRect buttonBounds(pos + sf::Vector2f(0, -size.y / 2), size + sf::Vector2f(0, size.y));
	sf::Vector2f mousePos = (sf::Vector2f)getMousePos(window);
	if (  (buttonBounds.contains(mousePos.x, mousePos.y)
		   && event.type == sf::Event::MouseButtonPressed 
		   && event.mouseButton.button == sf::Mouse::Left)
		|| holding) {
		
		add(mousePos.x - pos.x - selectedLength);
		holding = 1;
	}
	if (event.type == sf::Event::MouseButtonReleased)
		holding = 0;

	return 1.0 * selectedLength / size.x;
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(selected);
}

float Slider::get() {
	return 1.0 * selectedLength / size.x;
}