#include "Display.h"
#include "Format.h"
#include "Layout.h"
#include "Control.h"
#include "Source.h"

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
	bool keepLast(V& a) {
		if (!a.size()) return false;
		a[0] = a.back();
		a.resize(1);
		return true;
	}
	bool resetDisplay() { //keep last slide
		int ret = 0;
		ret |= keepLast(texts);
		ret |= keepLast(circles);
		ret |= keepLast(rectangles);
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

	template<class T>
	void display(sf::RenderWindow& window, std::vector<T>& v) {
		if (v.empty()) return;
		for (T& x : v) window.draw(x);
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		control::run(window, event);
	}
	void displayAll(sf::RenderWindow& window) {
		window.draw(layout::functionWindow::shape);
		window.draw(layout::displayWindow::shape);
		window.draw(layout::sourceWindow::shape);

		if (control::slideId < 0) return;

		control::update();
		control::draw(window);
		int id = control::getSlideId();
		display(window, rectangles[id]);
		display(window, texts[id]);

		source::hightlight(id - 1);
		source::draw(window);
	}
}