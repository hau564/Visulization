#include "Layer.h"
#include "Layout.h"
#include "Format.h"

#define PI 3.14159265359

void Layer::addArray(std::vector<int> a, sf::Vector2f pos, int cap)
{
	int n = a.size();
	if (cap < 0) cap = a.size();
	
	int length = layout::display::arrayBlockSize.x * cap;
	if (!pos.x) pos.x = layout::displayWindow::pos.x + layout::displayWindow::size.x / 2 - length / 2;
	if (!pos.y) pos.y = layout::displayWindow::pos.y + layout::displayWindow::size.y / 2 - layout::display::arrayBlockSize.y / 2 - up;
	
	for (int i = 0; i < n; ++i) {
		arr.push_back(ArrayNode(pos + sf::Vector2f(i * layout::display::arrayBlockSize.x, 0), a[i]));
	}
	for (int i = n; i < cap; ++i) {
		arr.push_back(ArrayNode(pos + sf::Vector2f(i * layout::display::arrayBlockSize.x, 0), 0));
		arr.back().setColor(style::denied);
	}
}

void Layer::addLinkedList(std::vector<int> llist, sf::Vector2f pos)
{
	if (llist.empty()) return;

	int n = llist.size();
	int arrowLength = layout::display::arrayBlockSize.x;

	int length = (n - 1) * (arrowLength + layout::display::arrayBlockSize.x) + layout::display::arrayBlockSize.x;
	if (!pos.x) pos.x = layout::displayWindow::pos.x + layout::displayWindow::size.x / 2 - length / 2;
	if (!pos.y) pos.y = layout::displayWindow::pos.y + layout::displayWindow::size.y / 2 - layout::display::arrayBlockSize.y / 2 - up;

	for (int i = 0; i < n; ++i) {
		list.push_back(LinkedListNode(pos + sf::Vector2f(i * (arrowLength + layout::display::arrayBlockSize.x), 0), llist[i]));
	}
	for (int i = 0; i < n - 1; ++i) {
		arrow.push_back(Arrow(list[i], list[i + 1]));
	}
}

void Layer::addDLinkedList(std::vector<int> llist, sf::Vector2f pos)
{
	if (llist.empty()) return;

	int n = llist.size();
	int arrowLength = layout::display::arrayBlockSize.x;

	int length = (n - 1) * (arrowLength + layout::display::arrayBlockSize.x) + layout::display::arrayBlockSize.x;
	if (!pos.x) pos.x = layout::displayWindow::pos.x + layout::displayWindow::size.x / 2 - length / 2;
	if (!pos.y) pos.y = layout::displayWindow::pos.y + layout::displayWindow::size.y / 2 - layout::display::arrayBlockSize.y / 2 - up;

	for (int i = 0; i < n; ++i) {
		list.push_back(LinkedListNode(pos + sf::Vector2f(i * (arrowLength + layout::display::arrayBlockSize.x), 0), llist[i]));
	}
	for (int i = 0; i < n - 1; ++i) {
		arrow.push_back(Arrow(list[i], list[i + 1]));
	}
	for (int i = 0; i < n - 1; ++i) {
		arrow.push_back(Arrow(list[i + 1], list[i]));
	}
}

sf::Vector2f getCircularPos(int i, int n) {
	sf::Vector2f pos;
	pos.x = layout::displayWindow::pos.x + layout::displayWindow::size.x / 2;
	pos.y = layout::displayWindow::pos.y + layout::displayWindow::size.y / 2 - 100;
	if (n == 1) {
		return pos - sf::Vector2f(layout::display::arrayBlockSize.x / 2, layout::display::arrayBlockSize.y / 2);
	}

	double angle = PI / 2 - 2 * PI / n * i;
	double t = 250;
	return pos + sf::Vector2f(t * cos(angle), -t * sin(angle));
}

void Layer::addCLinkedList(std::vector<int> llist, sf::Vector2f pos)
{
	if (llist.empty()) return;

	int n = llist.size();
	int arrowLength = layout::display::arrayBlockSize.x;

	int length = (n - 1) * (arrowLength + layout::display::arrayBlockSize.x) + layout::display::arrayBlockSize.x;
	if (!pos.x) pos.x = layout::displayWindow::pos.x + layout::displayWindow::size.x / 2 - length / 2;
	if (!pos.y) pos.y = layout::displayWindow::pos.y + layout::displayWindow::size.y / 2 - layout::display::arrayBlockSize.y / 2 - up;

	for (int i = 0; i < n; ++i) {
		list.push_back(LinkedListNode(getCircularPos(i, n), llist[i]));
	}
	for (int i = 0; i < n; ++i) {
		arrow.push_back(Arrow(list[i], list[(i + 1) % n]));
	}
}

void Layer::addTextAbove(std::string s, sf::Vector2f pos, sf::Vector2f displace) {
	text.push_back(sf::Text());
	text.back().setFont(layout::font);
	text.back().setCharacterSize(25);
	text.back().setString(s);
	text.back().setPosition(pos + displace);
	text.back().setFillColor(style::textColor);
}
void Layer::addTextAbove(std::string s, LinkedListNode node, sf::Vector2f displace) {
	addTextAbove(s, node.getPosition(), displace);
}
void Layer::addTextAbove(std::string s, ArrayNode node, sf::Vector2f displace) {
	addTextAbove(s, node.getPosition(), displace);
}

void Layer::addArrow(sf::Vector2f pos1, sf::Vector2f pos2)
{
	arrow.push_back(Arrow(pos1, pos2));
}

void Layer::clear() {
	text.clear();
	arrow.clear();
	arr.clear();
	list.clear();
}

void Layer::draw(sf::RenderWindow& window)
{
	for (Arrow& arw : arrow) arw.draw(window);
	for (ArrayNode& node : arr) node.draw(window);
	for (LinkedListNode& node : list) node.draw(window);
	for (sf::Text& text : text) window.draw(text);
}
