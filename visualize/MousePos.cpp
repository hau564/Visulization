#include "MousePos.h"

Vector2f getMousePos(sf::RenderWindow& window) {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	return Vector2f(worldPos.x, worldPos.y);
}