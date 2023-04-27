#include "Display.h"
#include "Format.h"
#include "Layout.h"
#include "Control.h"
#include "Source.h"
#include "iostream"
#include "fstream"

namespace display {
	std::vector<Layer> layers;

	void deleteDisplay() {
		layers.clear();	
		control::clear();
		source::clear();
	}

	void start() {
		control::start();

		std::ofstream out("outputVisualizeData.txt");

		for (ArrayNode node : layers.back().arr)
			out << (std::string)node.text.getString() << " ";
		for (LinkedListNode node : layers.back().list)
			out << (std::string)node.text.getString() << " ";

		out.close();
	}

	void addLayer(Layer layer, float weight, int checkPoint) {
		control::addSlide(weight);
		if (checkPoint) control::addCheckpoint();
		layers.push_back(layer);
	}

	void addSource(std::vector<std::string> code) {
		source::setSource(code);
	}

	std::vector<int> sourceOrder;
	void addSourceOrder(std::vector<int> ord) {
		sourceOrder = ord;
	}

	void run(sf::RenderWindow& window, sf::Event event) {
		if (!layers.empty())
			control::run(window, event);
	}

	void draw(sf::RenderWindow& window) {
		control::update();

		if (!control::slideTime.empty())
			control::draw(window);	
		
		int id = control::getSlideId();
		if (id >= 0 && id < (int)sourceOrder.size())
			source::hightlight(sourceOrder[id]);
		source::draw(window);

		if (!layers.empty()) layers[id].draw(window);

		if (source::lineCount) {
			//layout::sourceWindow::shape.setSize(sf::Vector2f(layout::sourceWindow::size.x, layout::sourceWindow::blockSize.y * source::lineCount));
			window.draw(layout::sourceWindow::shape);
		}
		//window.draw(layout::displayWindow::text);
		//window.draw(layout::functionWindow::text);
		//window.draw(layout::controlWindow::text);

		window.draw(layout::controlWindow::shape);
		window.draw(layout::displayWindow::shape);
		window.draw(layout::functionWindow::shape);
	}
}