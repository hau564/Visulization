#include "Layout.h"

namespace layout {
	int Width = 1920, Height = 1080;

	namespace functionWindow {
		sf::Vector2f size(200, 1000);
		sf::Vector2f pos(Width - size.x, Height - size.y);
		sf::Vector2f blockSize(200, 50);
		sf::RectangleShape shape;
	}

	namespace sourceWindow {
		sf::Vector2f size(400, 500);
		sf::Vector2f pos(0, Height - size.y);
		sf::RectangleShape shape;
	}

	namespace structuresBar {
		std::vector<std::string> labels = { "Static Array", "Dyamic Array", "Linked List (LL)", "Doubly LL" , "Circular LL", "Queue", "Stack" };

		sf::Vector2f pos(0, 0);
		sf::Vector2f blockSize(Width / 7, 50);
		int direction = 0;
		int charSize = 30;
		Taskbar bar;
	}

	void init() {
		functionWindow::shape.setPosition(functionWindow::pos);
		functionWindow::shape.setSize(functionWindow::size);
		functionWindow::shape.setFillColor(sf::Color::Transparent);
		functionWindow::shape.setOutlineThickness(2);
		functionWindow::shape.setOutlineColor(sf::Color::Black);

		sourceWindow::shape.setPosition(sourceWindow::pos);
		sourceWindow::shape.setSize(sourceWindow::size);
		sourceWindow::shape.setFillColor(sf::Color::Transparent);
		sourceWindow::shape.setOutlineThickness(2);
		sourceWindow::shape.setOutlineColor(sf::Color::Black);

		structuresBar::bar.create(layout::structuresBar::pos, layout::structuresBar::blockSize, style::button::faces, layout::structuresBar::labels, layout::structuresBar::direction, layout::structuresBar::charSize);
	}
}