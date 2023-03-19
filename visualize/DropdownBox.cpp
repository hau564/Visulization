#include "DropdownBox.h"

void DropdownBox::create(sf::Vector2f pos, sf::Vector2f labelButtonSize, sf::Vector2f blockSize, Button4Faces blockStyle, const std::vector<std::string> labelStr)
{
	int labelCount = labelStr.size();
	DropdownBox::droppedButtons.assign(labelCount, Button());
	DropdownBox::labelButton.create(pos, labelButtonSize, blockStyle, labelStr[0]);
	for (int i = 1; i < labelCount; ++i) {
		DropdownBox::droppedButtons[i].create(sf::Vector2f(pos.x, pos.y + labelButtonSize.y + blockSize.y * (i - 1)), blockSize, blockStyle, labelStr[i]);
	}
}

std::string DropdownBox::run(sf::RenderWindow &window, sf::Event event) {
	std::string stringPressed = "none";
	if (!dropped) {
		DropdownBox::dropped = (!DropdownBox::labelButton.isPressed() 
							  && DropdownBox::labelButton.run(window, event) == 2);
		if (!DropdownBox::labelButton.isPressed())
			dropped |= (DropdownBox::labelButton.run(window, event) == 2);
		else
			DropdownBox::labelButton.run(window, event);
	}
	else {
		bool stillDropped = false;
		if (DropdownBox::labelButton.isPressed()) 
			stillDropped |= DropdownBox::labelButton.run(window, event);
		else
			DropdownBox::labelButton.run(window, event);

		for (Button& btn : droppedButtons) {
			int status = btn.run(window, event);
			stillDropped |= status;
			if ((status) == 2) stringPressed = labelButton.getLabel() + ":" + btn.getLabel();
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			dropped = stillDropped;
	}
	if (labelButton.isPressed() && dropped) stringPressed = labelButton.getLabel();
	return stringPressed;
}

void DropdownBox::draw(sf::RenderWindow& window) {
	labelButton.draw(window);
	if (dropped) {
		for (Button &btn : droppedButtons)
			btn.draw(window);
	}
}

void DropdownBox::disDropped() {
	DropdownBox::dropped = false;
}
void DropdownBox::onDropped() {
	DropdownBox::dropped = true;
}
