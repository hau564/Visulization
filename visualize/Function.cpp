#include "Function.h"
#include "Style.h"
#include "MousePos.h"

void Function::create(sf::Vector2f pos, sf::Vector2f size, std::string label, std::vector<std::string> inputLabels)
{
	functionButton.create(pos, size, style::button::faces, label, Button::AutoOff);
	textboxes.assign(inputLabels.size(), Textbox());

	sf::Vector2f textPos = pos - sf::Vector2f(size.x, 0);
	for (int i = 0; i < (int)inputLabels.size(); ++i) {
		textboxes[i].create(textPos + sf::Vector2f(0, i * size.y), size + sf::Vector2f(-10, 0), inputLabels[i]);
	}

	go.create(textPos + sf::Vector2f(0, (int)inputLabels.size() * size.y), size + sf::Vector2f(-10, 0), style::button::faces, "Go");
}

bool Function::run(sf::RenderWindow& window, sf::Event event, std::vector<std::string>& get)
{
	if (active || functionButton.run(window, event) == Button::pressed) {
		for (Textbox& tbox : textboxes)
			tbox.run(window, event);
		if (go.run(window, event) == Button::pressed) {	
			for (Textbox& tbox : textboxes) {
				get.push_back(tbox.inputString);
				tbox.clear();
			}
			functionButton.run(window, event);
			active = 0;
			return true;
		}
		sf::Vector2f mousePos = getMousePos(window);
		if (active && event.type == sf::Event::MouseButtonPressed) {
			int stillActive = 0;
			for (Textbox& tbox : textboxes)
				stillActive |= tbox.box.contains(mousePos);
			active = stillActive;
			if (!active) functionButton.run(window, event);
		}
		else active = 1;
	}
	return false;
}

void Function::draw(sf::RenderWindow& window)
{
	functionButton.draw(window);
	if (active) {
		for (Textbox& tbox : textboxes)
			tbox.draw(window);
		go.draw(window);
	}
}

std::vector<std::string> Function::getInputVector() {
	std::vector<std::string> strs;
	for (Textbox& tbox : textboxes)
		strs.push_back(tbox.inputString);
	return strs;
}