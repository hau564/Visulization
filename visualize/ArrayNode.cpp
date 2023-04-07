#include "ArrayNode.h"
#include "Format.h"
#include "Layout.h"
#include "Style.h"

void ArrayNode::create(sf::Vector2f pos, int x)
{
	bound = layout::display::arrayBlock;
	sf::Vector2f size = layout::display::arrayBlockSize;
	bound.setPosition(pos);

	text.setFont(layout::font);
	text.setCharacterSize(size.y / 2.0);
	text.setString(format::toString(x));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));
	text.setFillColor(sf::Color::Black);
}

void ArrayNode::setValue(int x) {
	sf::Vector2f pos = bound.getPosition();
	sf::Vector2f size = bound.getSize();

	text.setString(format::toString(x));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));	
}

ArrayNode::ArrayNode(sf::Vector2f pos, int x)
{
	create(pos, x);
}

void ArrayNode::setColor(sf::Color color)
{
	bound.setFillColor(color);
}

void ArrayNode::draw(sf::RenderWindow& window)
{
	window.draw(bound);
	window.draw(text);
}

void ArrayNode::beNormal() {
	bound.setFillColor(layout::display::normalColor);
}

void ArrayNode::beTarget() {
	bound.setFillColor(layout::display::targetColor);
}

void ArrayNode::beVisited() {
	bound.setFillColor(layout::display::visitedColor);
}

sf::Vector2f ArrayNode::getPosition() {
	return bound.getPosition();
}