#include "Source.h"
#include "Style.h"
#include "Layout.h"
#include "Color.h"

namespace source {
	std::vector<sf::Text> texts;
	std::vector<sf::RectangleShape> rects;
	int cnt, hightlightPos = 0, prevFocused = 0, lineCount;
	sf::Font font;
	void init() {
		cnt = layout::sourceWindow::size.y / layout::sourceWindow::blockSize.y;
		texts.assign(cnt, sf::Text());
		rects.assign(cnt, sf::RectangleShape());

		for (int i = 0; i < cnt; ++i) {
			sf::Vector2f pos(layout::sourceWindow::pos.x, layout::sourceWindow::pos.y + layout::sourceWindow::blockSize.y * i);
			rects[i].setPosition(pos);
			rects[i].setSize(layout::sourceWindow::blockSize);
			rects[i].setOutlineThickness(0);
			
			rects[i].setFillColor(sf::Color::White);

			font.loadFromFile("font/cour.ttf");
			texts[i].setFont(font);

			texts[i].setString("ÂÖgq|");
			texts[i].setCharacterSize(layout::sourceWindow::fontSize);
			sf::FloatRect textRect = texts[i].getLocalBounds();
			//texts[i].setOrigin(sf::Vector2f(0, textRect.height / 2));
			texts[i].setPosition(pos.x + 10, pos.y - 2);// +layout::sourceWindow::blockSize.y / 2.0);
			texts[i].setFillColor(sf::Color::Black);
			texts[i].setString("");
		}
	}	
	void clear() {
		for (int i = 0; i < cnt; ++i) {
			texts[i].setString("");
			rects[i].setFillColor(sf::Color::White);
		}
		lineCount = 0;
	}

	void setSource(std::vector<std::string> strs) {
		lineCount = (int)strs.size();
		for (int i = 0; i < (int)strs.size(); ++i) {
			texts[i].setString(strs[i]);
		}
	}

	void hightlight(int pos) {
		if (rects.empty()) return;
		rects[hightlightPos].setFillColor(sf::Color::White);
		if (pos < 0 || pos >= lineCount) return;
		hightlightPos = pos;
		rects[hightlightPos].setFillColor(sf::Color::Cyan);
	}
	void draw(sf::RenderWindow& window) {
		for (sf::RectangleShape& rect : rects)
			window.draw(rect);
		for (sf::Text& text : texts)
			window.draw(text);
	}
}