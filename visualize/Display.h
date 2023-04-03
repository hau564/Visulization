#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Layer.h"

namespace display {
	extern std::vector<Layer> layers;
	
	extern void deleteDisplay();
	extern void start();
	extern void addLayer(Layer layer, float weight = 1.0, int checkPoint = 1);
	extern void addSource(std::vector<std::string> code);

	extern std::vector<int> sourceOrder;
	extern void addSourceOrder(std::vector<int> ord);

	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}