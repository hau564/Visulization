#include "MenuBar.h"

void MenuBar::create(sf::Vector2f pos, sf::Vector2f blockSize, sf::Vector2f dropSize, Button4Faces blockStyle, Button4Faces dropStyle, const std::vector<std::vector<std::string>> strings)
{
	int dropBoxCount = strings.size();
	MenuBar::dropdownBoxes.assign(dropBoxCount, DropdownBox());
	for (int i = 0; i < dropBoxCount; ++i) {
		MenuBar::dropdownBoxes[i].create(sf::Vector2f(pos.x + blockSize.x * i, pos.y), blockSize, dropSize, blockStyle, strings[i]);
	}
}

std::string MenuBar::run(sf::RenderWindow& window, sf::Event event)
{
	std::string stringPressed = "none";
	for (DropdownBox& drop : dropdownBoxes) {
		std::string status = drop.run(window, event);
		if (status != "none")
			stringPressed = status;
	}

	anyDropped = false;
	for (DropdownBox& drop : dropdownBoxes)
		anyDropped |= drop.dropped;

	if (anyDropped) {
		for (DropdownBox& drop : dropdownBoxes) {
			if (drop.labelButton.state > 0) {
				for (DropdownBox& drop : dropdownBoxes) drop.disDropped();
				drop.onDropped();
			}
		}
	}

	return stringPressed;
}

void MenuBar::draw(sf::RenderWindow& window)
{
	for (DropdownBox& drop : MenuBar::dropdownBoxes) drop.draw(window);
}
