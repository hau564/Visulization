#include "Taskbar.h"

void Taskbar::create(sf::Vector2f pos, sf::Vector2f blockSize, sf::Vector2f dropSize, Button4Faces blockStyle, Button4Faces dropStyle, const std::vector<std::vector<std::string>> strings)
{
	int dropBoxCount = strings.size();
	Taskbar::dropdownBoxes.assign(dropBoxCount, DropdownBox());
	for (int i = 0; i < dropBoxCount; ++i) {
		Taskbar::dropdownBoxes[i].create(sf::Vector2f(pos.x + blockSize.x * i, pos.y), blockSize, dropSize, blockStyle, strings[i]);
	}
}

std::string Taskbar::run(sf::RenderWindow& window, sf::Event event)
{
	std::string stringPressed = "none";
	for (DropdownBox& drop : dropdownBoxes) {
		std::string status = drop.run(window, event);
		if (status != drop.labelButton.getLabel())
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

void Taskbar::draw(sf::RenderWindow& window)
{
	for (DropdownBox& drop : Taskbar::dropdownBoxes) drop.draw(window);
}
