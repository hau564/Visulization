#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

namespace style {
	int Width = 1920;
	int Height = 1080;

	sf::Color backgroundColor = sf::Color::White;


	namespace button {
		ButtonFace normal{
			2,
			sf::Color::White,
			sf::Color::Black
		};
		ButtonFace focused{
			3,
			sf::Color::White,
			sf::Color::Black
		};
		ButtonFace pressed{
			4,
			sf::Color::White,
			sf::Color::Black
		};
		ButtonFace disabled{
			2,
			sf::Color::Transparent,
			sf::Color::Black
		};

		Button4Faces faces{ normal, focused, pressed, disabled };
	}


	namespace menuBar {
		namespace blockStyle {
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

			Button4Faces faces{ normal, focused, pressed, disabled };
		}

		namespace dropStyle {
			ButtonFace normal{
				1,
				sf::Color::White,
				sf::Color::Black
			};
			ButtonFace focused{
				2,
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

			Button4Faces faces{ normal, focused, pressed, disabled };
		}
	}
};