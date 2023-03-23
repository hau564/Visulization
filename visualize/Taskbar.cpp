#include "Taskbar.h"

void Taskbar::create(sf::Vector2f pos, sf::Vector2f size, Button4Faces style, std::vector<std::string> labels, int _w, int charSize) {
	int labelCount = labels.size();

	w = _w;
	
	buttons.assign(labelCount, Button());
	for (int i = 0; i < labelCount; ++i) {
		buttons[i].create(sf::Vector2f(pos.x + size.x * i * dir[w], pos.y + size.y * i * dir[w + 1]), size, style, labels[i], Button::OnOffMode, charSize);
	}
}

std::string Taskbar::run(sf::RenderWindow& window, sf::Event event)
{
	std::string ans = "none";
	for (int i = 0; i < (int)buttons.size(); ++i) {
		if (buttons[i].run(window, event) == Button::pressed) {
			ans = buttons[i].getLabel();
			for (int j = 0; j < (int)buttons.size(); ++j) {
				if (i != j) {
					buttons[j].resetState();
				}
			}
		}
	}
	return ans;
}

void Taskbar::draw(sf::RenderWindow& window) {
	for (Button butt : buttons) if (!butt.isPressed() && !butt.isFocused()) butt.draw(window);
	for (Button butt : buttons) if (butt.isPressed() || butt.isFocused()) butt.draw(window);
}
