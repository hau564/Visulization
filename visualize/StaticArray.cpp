#include "StaticArray.h"
#include "Style.h"
#include "Layout.h"
#include "MousePos.h"
#include "Display.h"
#include "Control.h"
#include "Format.h"
#include "Source.h"

namespace staticArray {
	std::vector<Function> functions;
	void init() {
		functions.assign(2, Function());
		sf::Vector2f pos = layout::functionWindow::pos;
		sf::Vector2f blockSize = layout::functionWindow::blockSize;
		functions[0].create(pos, blockSize, "Create", { "Size: ", "Values: " });
		functions[1].create(pos + sf::Vector2f(0, 1 * blockSize.y), blockSize, "Update", { "Pos: ", "Value: " });
	}

	std::vector<int> arr;
	void createArray(std::vector<std::vector<sf::Text>>& texts, std::vector<std::vector<sf::RectangleShape>>& rectangles) {
		int n = arr.size();
		int length = n * layout::display::arrayBlockSize.x;
		sf::Vector2f startPos(layout::displayWindow::pos.x + (layout::displayWindow::size.x - length) / 2,
			layout::displayWindow::pos.y + (layout::displayWindow::size.y - layout::display::arrayBlockSize.y) / 2 - 50);

		rectangles.push_back(std::vector<sf::RectangleShape>());
		rectangles[0].assign(n, layout::display::arrayBlock);
		texts.push_back(std::vector<sf::Text>());
		texts[0].assign(n, sf::Text());

		for (int i = 0; i < n; ++i) {
			rectangles[0][i].setPosition(startPos + sf::Vector2f(i * layout::display::arrayBlockSize.x + i, 0));
			display::setTextRectangle(texts[0][i], rectangles[0][i], format::toString(arr[i]));
		}
	}
	void createSlides(std::string _n, std::string _values, std::vector<std::vector<sf::Text>>& texts, std::vector<std::vector<sf::RectangleShape>>& rectangles) {
		int n;
		if (!format::toInt(_n, n)) return;
		if (!format::toVectorInt(_values, arr)) return;

		if (!n) n = rand() % 15 + 1;
		if (arr.empty()) {
			while (arr.size() < n) arr.push_back(rand() % 100);
		}
		else {
			while (arr.size() < n) arr.push_back(0);
		}

		texts.clear();
		rectangles.clear();
		control::clear();
		control::start();
		control::addSlide();

		createArray(texts, rectangles);
	}

	void updateSlides(std::string _pos, std::string _val, std::vector<std::vector<sf::Text>>& texts, std::vector<std::vector<sf::RectangleShape>>& rectangles) {
		if (arr.empty()) return;
		int pos, val;
		if (!format::toInt(_pos, pos)) return;
		if (!format::toInt(_val, val)) return;
		if (pos < 1 || pos >(int)arr.size()) return;

		if (!val) val = rand() % 100;
		texts.clear();
		rectangles.clear();

		source::clear();
		source::setSource({ "arr[pos] = val" });

		control::clear();
		control::start();
		for (int i = 0; i < 3; ++i) {
			control::addSlide();
			control::addCheckpoint();
		}
		createArray(texts, rectangles);

		for (int i = 0; i < 2; ++i) {
			texts.push_back(texts[0]);
			rectangles.push_back(rectangles[0]);
		}
		rectangles[1][pos - 1].setFillColor(layout::display::targetColor);
		display::setTextRectangle(texts[2][pos - 1],rectangles[2][pos - 1], format::toString(val));
		arr[pos - 1] = val;
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get(0);
		if (functions[0].run(window, event, get)) createSlides(get[0], get[1], display::texts, display::rectangles);
		if (functions[1].run(window, event, get)) updateSlides(get[0], get[1], display::texts, display::rectangles);
		display::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		for (Function& func : functions)
			if (!func.functionButton.isPressed() && !func.functionButton.isFocused())
				func.draw(window);
		for (Function& func : functions)
			if (func.functionButton.isPressed() || func.functionButton.isFocused())
				func.draw(window);

		display::displayAll(window);
	}
}

