#include "StaticArray.h"
#include "Style.h"
#include "Layout.h"
#include "MousePos.h"

namespace staticArray {
	Button createButton, changeButton;
	Textbox getSize, getValues;
	Button goCreate;

	void init() {
		createButton.create(layout::functionWindow::pos, layout::functionWindow::blockSize, style::button::faces, "Create", Button::AutoOff);
		changeButton.create(layout::functionWindow::pos + sf::Vector2f(0, layout::functionWindow::blockSize.y), layout::functionWindow::blockSize, style::button::faces, "Change", Button::AutoOff);
		
		getSize.create(createButton.pos - sf::Vector2f(createButton.size.x, 0), createButton.size - sf::Vector2f(8, 0), "Size: ", 9);
		getValues.create(createButton.pos - sf::Vector2f(createButton.size.x, -createButton.size.y) - sf::Vector2f(8, 0), createButton.size, "Values: ");
		goCreate.create(createButton.pos - sf::Vector2f(createButton.size.x, -2 * createButton.size.y), createButton.size - sf::Vector2f(8, 0), style::button::faces, "Go");
	}

	int createActive = 0;
	void Create(sf::RenderWindow& window, sf::Event event) {
		getSize.run(window, event);
		getValues.run(window, event);
		goCreate.run(window, event);

		sf::Vector2f mousePos = getMousePos(window);
		if (createActive && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !getSize.box.contains(mousePos) && !getValues.box.contains(mousePos)) {
			createButton.run(window, event);
			createActive = 0;
		}
		else createActive = 1;

	}

	void run(sf::RenderWindow& window, sf::Event event){
		if (createActive || createButton.run(window, event) == Button::pressed) Create(window, event);
		changeButton.run(window, event);
	}

	void draw(sf::RenderWindow& window){
		window.draw(layout::functionWindow::shape);
		window.draw(layout::sourceWindow::shape);

		if (!createButton.isPressed() && !createButton.isFocused()) createButton.draw(window);
		changeButton.draw(window);
		if (createButton.isPressed() || createButton.isFocused()) createButton.draw(window);

		if (createActive) {
			getSize.draw(window);
			getValues.draw(window);
			goCreate.draw(window);
		}
	}
}

