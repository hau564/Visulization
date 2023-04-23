#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

namespace style {
	extern int Width;
	extern int Height;

	extern sf::Color backgroundColor;
	extern sf::Color outlineColor;
	extern sf::Color textColor;
	extern sf::Color codeHighlight;
	extern sf::Color target;
	extern sf::Color pointTarget;
	extern sf::Color denied;

	namespace button {
		extern ButtonFace normal;
		extern ButtonFace focused;
		extern ButtonFace pressed;
		extern ButtonFace disabled;
		extern Button4Faces faces;

		namespace defaultButton{
			extern ButtonFace normal;
			extern ButtonFace focused;
			extern ButtonFace pressed;
			extern ButtonFace disabled;
			extern Button4Faces faces;
		}

		namespace textButton {
			extern ButtonFace normal;
			extern ButtonFace focused;
			extern ButtonFace pressed;
			extern ButtonFace disabled;
			extern Button4Faces faces;
		}
	}

	extern void refresh();
};