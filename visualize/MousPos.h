#pragma once

#include<SFML/Graphics.hpp>

using namespace sf;

Vector2i getMousePos(RenderWindow& window) {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	return Vector2i(worldPos.x, worldPos.y);
}