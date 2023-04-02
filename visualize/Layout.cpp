#include "Layout.h"
#include "Style.h"
#include "Color.h"
namespace layout {
	int Width = style::Width, Height = style::Height;
	sf::Font font; 


	namespace controlWindow {
		sf::Vector2f size(Width, 60);
		sf::Vector2f pos(0, Height - size.y);
		sf::RectangleShape shape;

		sf::Vector2f playSize(40, 40);
		sf::Vector2f playPos((Width - playSize.x) / 2, pos.y + (size.y - playSize.y) / 2 );

		int dis = 50;
		sf::Vector2f prevSize = playSize;
		sf::Vector2f prevPos(playPos.x - dis - prevSize.x, playPos.y);

		sf::Vector2f nextSize = prevSize;
		sf::Vector2f nextPos(playPos.x + playSize.x + dis, playPos.y);

		sf::Vector2f toStartSize(10.0 / 7.0 * playSize.x, playSize.y);
		sf::Vector2f toStartPos(prevPos.x - dis - toStartSize.x, playPos.y);

		sf::Vector2f toEndSize = toStartSize;
		sf::Vector2f toEndPos(nextPos.x + nextSize.x + dis, playPos.y);

		sf::Vector2f speedSize(200, 10);
		sf::Vector2f speedPos(100, pos.y + (size.y - speedSize.y) / 2);
		sf::Color speedBack = color::whiteGray;
		sf::Color speedSele = sf::Color::Black;
	}

	namespace functionWindow {
		sf::Vector2f size(200, 1000 - controlWindow::size.y);
		sf::Vector2f pos(Width - size.x, Height - 1000);
		sf::Vector2f blockSize(200, 50);
		sf::RectangleShape shape;
	}

	namespace sourceWindow {
		sf::Vector2f size(400, functionWindow::size.y);
		sf::Vector2f pos(0, functionWindow::pos.y);
		sf::Vector2f blockSize(size.x, 50);
		sf::RectangleShape shape;

		int fontSize = 30;
	}

	namespace displayWindow {
		sf::Vector2f size(Width - functionWindow::size.x - sourceWindow::size.x, functionWindow::size.y);
		sf::Vector2f pos(functionWindow::pos.x - size.x, functionWindow::pos.y);
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

	namespace display {

		sf::Color normalColor = sf::Color::Black;
		sf::Color visitedColor = sf::Color::Cyan;
		sf::Color considerColor = sf::Color::Blue;
		sf::Color targetColor = sf::Color::Green;

		sf::Vector2f arrayBlockSize(50, 50);
		sf::RectangleShape arrayBlock;
	}

	void setRectangle(sf::RectangleShape& rect, sf::Vector2f pos, sf::Vector2f size, sf::Color backColor, int outThick, sf::Color outColor) {
		rect.setPosition(pos);
		rect.setSize(size);
		rect.setFillColor(backColor);
		rect.setOutlineThickness(outThick);
		rect.setOutlineColor(outColor);
	}

	void init() {
		font.loadFromFile("font/arial.ttf");

		setRectangle(functionWindow::shape, functionWindow::pos, functionWindow::size, sf::Color::Transparent, 1, sf::Color::Black);
		setRectangle(sourceWindow::shape, sourceWindow::pos, sourceWindow::size, sf::Color::Transparent, 1, sf::Color::Black);
		setRectangle(displayWindow::shape, displayWindow::pos, displayWindow::size, sf::Color::Transparent, 1, sf::Color::Black);
		setRectangle(display::arrayBlock, sf::Vector2f(0, 0), display::arrayBlockSize, sf::Color::Transparent, 1, sf::Color::Black);

		structuresBar::bar.create(layout::structuresBar::pos, layout::structuresBar::blockSize, style::button::faces, layout::structuresBar::labels, layout::structuresBar::direction, layout::structuresBar::charSize);
	}
}