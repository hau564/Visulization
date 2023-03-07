#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

namespace style {
	int Width = 1920;
	int Height = 1200;

	sf::Color backgroundColor = sf::Color::White;

	sf::Font font;
	void init() {
		font.loadFromFile("font/arial.ttf");
	}
	namespace button {
		ButtonFace normal{
			1,
			sf::Color::White,
			sf::Color::Black
		};
		ButtonFace focused{
			1,
			sf::Color::Green,
			sf::Color::Black
		};
		ButtonFace pressed{
			1,
			sf::Color::Red,
			sf::Color::Black
		};
		ButtonFace disabled{
			1,
			sf::Color::Transparent,
			sf::Color::Black
		};

		Button4Faces allFaces{ normal, focused, pressed, disabled };
	}
};