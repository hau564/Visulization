#include "Layer.h"
#include "Layout.h"
#include "Format.h"

void Layer::addArray(std::vector<int> a, sf::Vector2f pos)
{
	int n = a.size();
	
	int length = layout::display::arrayBlockSize.x * n;
	if (!pos.x) pos.x = layout::displayWindow::pos.x + layout::displayWindow::size.x / 2 - length / 2;
	if (!pos.y) pos.y = layout::displayWindow::pos.y + layout::displayWindow::size.y / 2 - layout::display::arrayBlockSize.y / 2 - up;
	
	for (int i = 0; i < n; ++i) {
		arr.push_back(ArrayNode(pos + sf::Vector2f(i * layout::display::arrayBlockSize.x, 0), a[i]));
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

void Layer::addTextAbove(std::string s, LinkedListNode node, sf::Vector2f displace) {
	text.push_back(sf::Text());
	text.back().setFont(layout::font);
	text.back().setCharacterSize(25);
	text.back().setString(s);
	text.back().setPosition(node.getPosition() + displace);
	text.back().setFillColor(sf::Color::Black);
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
