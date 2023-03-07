#pragma once

#include "Button.h"
#include "Style.h"
#include<SFML/Graphics.hpp>

namespace layout {
	namespace taskbar {
		const std::vector<std::vector<std::string>> allTasks{
			{"Static Array", "Create", "Add", "Delete"},
			{"Dyamic Array", "Create", "Add", "Delete"},
			{"Linked List", "Create", "Insert", "Delete"},
			{"Doubly Linked List", "Create", "Insert", "Delete"},
			{"Cirular Linked List", "Create", "Insert", "Delete"},
			{"Stack", "Create", "Push", "Pop"},
			{"Queue", "Create", "Push", "Pop"},
			{"Settings"}
		};
		sf::Vector2f pos{ 0, 0 };
		sf::Vector2f blockSize{ 1920 / 8, 40 };
		sf::Vector2f dropBlockSize{ 1920 / 8, 40 };
	}
}