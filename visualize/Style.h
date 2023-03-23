#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

namespace style {
	extern int Width;
	extern int Height;

	extern sf::Color backgroundColor;


	namespace button {
		extern ButtonFace normal;
		extern ButtonFace focused;
		extern ButtonFace pressed;
		extern ButtonFace disabled;
		extern Button4Faces faces;

		namespace textButton {
			extern ButtonFace normal;
			extern ButtonFace focused;
			extern ButtonFace pressed;
			extern ButtonFace disabled;
			extern Button4Faces faces;
		}
	}


	namespace menuBar {
		namespace blockStyle {
			extern ButtonFace normal;
			extern ButtonFace focused;
			extern ButtonFace pressed;
			extern ButtonFace disabled;
			extern Button4Faces faces;
		}
	}
};