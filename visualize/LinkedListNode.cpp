#include "LinkedListNode.h"
#include "Format.h"
#include "Layout.h"
#include "Style.h"

void LinkedListNode::create(sf::Vector2f pos, int x)
{
	bound = layout::display::linkedListBlock;
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

LinkedListNode::LinkedListNode(sf::Vector2f pos, int x)
{
	create(pos, x);
}

void LinkedListNode::setColor(sf::Color color)
{
	bound.setFillColor(color);
}

void LinkedListNode::draw(sf::RenderWindow& window)
{
	window.draw(bound);
	window.draw(text);
}

void LinkedListNode::beNormal() {
	bound.setFillColor(layout::display::normalColor);
}

void LinkedListNode::beTarget() {
	bound.setFillColor(layout::display::targetColor);
}

void LinkedListNode::beVisited() {
	bound.setFillColor(layout::display::visitedColor);
}

sf::Vector2f LinkedListNode::getPosition() {
	return bound.getPosition();
}
