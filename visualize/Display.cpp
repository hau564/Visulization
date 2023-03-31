#include "Display.h"
#include "Format.h"
#include "Layout.h"

namespace display {
	std::vector<std::vector<sf::Text>> texts;
	std::vector<std::vector<sf::CircleShape>> circles;
	std::vector<std::vector<sf::RectangleShape>> rectangles;

	void clear() {
		texts.clear();
		circles.clear();
		rectangles.clear();
	}
	template<class V>
	bool resizeBack(V& a) {
		if (!a.size()) return false;
		a[0] = a.back();
		a.resize(1);
		return true;
	}
	bool resetDisplay() {
		int ret = 0;
		ret |= resizeBack(texts);
		ret |= resizeBack(circles);
		ret |= resizeBack(rectangles);
		return ret;
	}

	std::vector<int> arr;
	std::vector<int> ll;

	void setTextRectangle(sf::Text& text, sf::RectangleShape& rect, std::string s) {
		sf::Vector2f pos = rect.getPosition(), size = rect.getSize();
		text.setFont(layout::font);
		text.setString(s);
		text.setCharacterSize(size.y / 2);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));
		text.setFillColor(sf::Color::Black);
	}

	clock_t displayStart;
	namespace array {
		int arraySize = 0;

		void create(std::string _n, std::string _values) {
			int n;
			if (!format::toInt(_n, n)) return;
			if (!format::toVectorInt(_values, arr)) return;
			
			arraySize = n;
			while (arr.size() < n) arr.push_back(0);
			clear();

			displayStart = clock();
			int length = n * layout::display::arrayBlockSize.x;
			sf::Vector2f startPos(layout::displayWindow::pos.x + (layout::displayWindow::size.x - length) / 2,
								  layout::displayWindow::pos.y + (layout::displayWindow::size.y - layout::display::arrayBlockSize.y) / 2 - 50);
		
			rectangles.push_back(std::vector<sf::RectangleShape>());
			rectangles[0].assign(n, layout::display::arrayBlock);
			texts.push_back(std::vector<sf::Text>());
			texts[0].assign(n, sf::Text());

			for (int i = 0; i < n; ++i) {
				rectangles[0][i].setPosition(startPos + sf::Vector2f(i * layout::display::arrayBlockSize.x + i, 0));
				setTextRectangle(texts[0][i], rectangles[0][i], format::toString(arr[i]));
			}
		}
		void create(std::vector<std::string> inputStrs) {create(inputStrs[0], inputStrs[1]);}

		void update(std::string _pos, std::string _val) {
			int pos, val;
			if (!format::toInt(_pos, pos)) return;
			if (!format::toInt(_val, val)) return;
			if (!arraySize) return;
			if (pos > arraySize || pos < 1) return;

			resetDisplay();

			displayStart = clock();
			for (int i = 0; i < 2; ++i) {
				rectangles.push_back(rectangles[0]);
				texts.push_back(texts[0]);
			}
			rectangles[1][pos - 1].setFillColor(layout::display::targetColor);
			setTextRectangle(texts[2][pos - 1], rectangles[2][pos - 1], format::toString(val));
		}
		void update(std::vector<std::string> inputStrs) { update(inputStrs[0], inputStrs[1]); }
	}

	void displayAll(sf::RenderWindow& window) {
		if (rectangles.empty()) return;

		float t = (clock() - displayStart) / CLOCKS_PER_SEC;
		int slideId = std::min((int)rectangles.size() - 1, (int)t);
		
		for (sf::RectangleShape& rect : rectangles[slideId])
			window.draw(rect);
		for (sf::Text& text : texts[slideId])
			window.draw(text);
	}
}