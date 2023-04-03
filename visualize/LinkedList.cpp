#include "LinkedList.h"
#include "Layout.h"
#include "Display.h"
#include "Format.h"

namespace linkedList {
	std::vector<int> list;
	Function create, del, insert, search;

	void init() {
		create.create(layout::functionWindow::pos, layout::functionWindow::blockSize, "Create", {"Size: ", "Values: "});
		insert.create(layout::functionWindow::pos + sf::Vector2f(0, 1*layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Insert", { "Pos: ", "Value: "});
		del.create(layout::functionWindow::pos + sf::Vector2f(0,  2 * layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Delete", { "Pos: "});
		search.create(layout::functionWindow::pos + sf::Vector2f(0, 3*layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, "Search", { "First of: "});
	}

	void Create(std::string _n, std::string _values) {
		int n;
		if (!format::toInt(_n, n)) return;
		if (!format::toVectorInt(_values, list)) return;

		if (_n == "") n = rand() % 10 + 1;
		if (list.empty()) {
			for (int i = 0; i < n; ++i)
				list.push_back(rand() % 100);
		}
		else {
			while (list.size() < n)
				list.push_back(0);
		}

		display::deleteDisplay();

		Layer layer;
		layer.addLinkedList(list);
		layer.addTextAbove("head", layer.list[0], {-30, -30});
		layer.addTextAbove("tail", layer.list.back(), {30, -30});
		display::addLayer(layer);		
		
		display::start();
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get;
		if (create.run(window, event, get)) Create(get[0], get[1]);
		if (insert.run(window, event, get));
		if (del.run(window, event, get));
		if (search.run(window, event, get));

		display::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		create.draw(window);
		insert.draw(window);
		del.draw(window);
		search.draw(window);

		if (create.functionButton.isPressed() || create.functionButton.isFocused()) create.draw(window);
		if (insert.functionButton.isPressed() || insert.functionButton.isFocused()) insert.draw(window);
		if (del.functionButton.isPressed() || del.functionButton.isFocused()) del.draw(window);
		if (search.functionButton.isPressed() || search.functionButton.isFocused()) search.draw(window);

		display::draw(window);
	}
}