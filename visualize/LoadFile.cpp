#include "LoadFile.h"
#include "Layout.h"
#include "Style.h"
#include "iostream"
#include "fstream"

namespace loadFile {
	Textbox address;
	Button load;
	void init() {
		int Width = 370, Height = 130;
		sf::Vector2f size(300, 60);
		address.create({ (Width - size.x) / 2, 0}, size, "Address: ");
		load.create({ (Width - size.x) / 2, size.y}, {300, 60}, style::button::faces, "Load");
	}
	void get(std::vector<std::string>& strs) {
		int Width = 370, Height = 130;
        sf::RenderWindow window(sf::VideoMode(Width, Height), "File", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);

		while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
					address.clear();
					address.isActive = 0;
					load.resetState();
					return;
                }
				address.run(window, event);
				if (load.run(window, event) == Button::pressed) window.close();
            }

            window.clear(style::backgroundColor);

			address.draw(window);
			load.draw(window);

            window.display();
        }

		std::string filename = "";
		for (char c : address.inputString)
			if (c != '"') filename += c;
		address.clear();
		address.isActive = 0;
		load.resetState();

		std::ifstream file(filename);

		if (!file.is_open()) {
			std::cout << "Could not open file\n";
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			strs.push_back(line);
		}

		file.close();		
	}
}