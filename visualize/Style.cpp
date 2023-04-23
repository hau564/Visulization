#include "Style.h"
#include<iostream>
#include<fstream>

namespace style {
	int Width = 1920;
	int Height = 1080;

	sf::Color backgroundColor = sf::Color::White;
	sf::Color outlineColor = sf::Color::Black;
	sf::Color textColor = sf::Color::Black;
	sf::Color codeHighlight = sf::Color::Cyan;
	sf::Color target = sf::Color::Green;
	sf::Color pointTarget = sf::Color::Cyan;
	sf::Color denied = sf::Color::Red;

	namespace button {
		ButtonFace normal{
			2,
			style::backgroundColor,
			style::outlineColor
		};
		ButtonFace focused{
			3,
			style::backgroundColor,
			style::outlineColor
		};
		ButtonFace pressed{
			4,
			style::backgroundColor,
			style::outlineColor
		};
		ButtonFace disabled{
			2,
			sf::Color::Transparent,
			style::outlineColor
		};

		Button4Faces faces{ normal, focused, pressed, disabled };

		namespace defaultButton {
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
				style::outlineColor
			};

			Button4Faces faces{ normal, focused, pressed, disabled };
		}
		namespace textButton {
			ButtonFace normal{
				2,
				style::backgroundColor,
				style::outlineColor
			};
			ButtonFace focused{
				3,
				style::backgroundColor,
				style::outlineColor
			};
			ButtonFace pressed{
				4,
				style::backgroundColor,
				style::outlineColor
			};
			ButtonFace disabled{
				2,
				sf::Color::Transparent,
				style::outlineColor
			};

			Button4Faces faces{ normal, focused, pressed, disabled };
		}
	}


	sf::Color loadColor(const std::string file) {
		std::ifstream inp(file.c_str());
		int r, g, b;
		inp >> r >> g >> b;
		inp.close();
		return sf::Color(r, g, b);
	}

	void refresh() {
		backgroundColor = loadColor("setting/background.txt");
		textColor = loadColor("setting/text.txt");
		outlineColor = loadColor("setting/outline.txt");
		codeHighlight = loadColor("setting/highlightcode.txt");
		target = loadColor("setting/target.txt");
		pointTarget = loadColor("setting/pointingtarget.txt");
		denied = loadColor("setting/denied.txt");

		button::normal.backgroundColor = button::focused.backgroundColor = button::pressed.backgroundColor
			= button::textButton::normal.backgroundColor = button::textButton::focused.backgroundColor = button::textButton::pressed.backgroundColor = backgroundColor;

		button::normal.outlineColor = button::focused.outlineColor = button::pressed.outlineColor
			= button::textButton::normal.outlineColor = button::textButton::focused.outlineColor = button::textButton::pressed.outlineColor = outlineColor;
		
		button::faces = Button4Faces{ button::normal, button::focused, button::pressed, button::disabled };
		button::textButton::faces = Button4Faces{ button::textButton::normal, button::textButton::focused, button::textButton::pressed, button::textButton::disabled };
	};
}