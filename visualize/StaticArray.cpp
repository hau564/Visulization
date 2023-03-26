#include "StaticArray.h"
#include "Style.h"
#include "Layout.h"
#include "MousePos.h"

namespace staticArray {
	std::vector<Function> functions;
	void init() {
		functions.assign(2, Function());
		sf::Vector2f pos = layout::functionWindow::pos;
		sf::Vector2f blockSize = layout::functionWindow::blockSize;
		functions[0].create(pos, blockSize, "Create", {"Size: ", "Values: "});
		functions[1].create(pos + sf::Vector2f(0, 1 * blockSize.y), blockSize, "Update", {"Pos: ", "Value: "});
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		std::vector<std::string> get(0);
		if (functions[0].run(window, event, get));
		if (functions[1].run(window, event, get));

		if (get.size()) {
			for (std::string s : get) 
				std::cout << s << "\n";
		}
	}

	void draw(sf::RenderWindow& window) {
		window.draw(layout::functionWindow::shape);

		for (Function& func : functions)
			if (!func.functionButton.isPressed() && !func.functionButton.isFocused())
				func.draw(window);
		for (Function& func : functions)
			if (func.functionButton.isPressed() || func.functionButton.isFocused())
				func.draw(window);
	}
}

