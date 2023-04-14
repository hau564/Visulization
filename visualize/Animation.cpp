#include "Animation.h"

namespace animation {
	sf::Vector2f getPos(sf::Vector2f pos1, sf::Vector2f pos2, float r) {
		return { pos1.x + r * (pos2.x - pos1.x) , pos1.y + r * (pos2.y - pos1.y) };
	}

	Arrow getArrow(Arrow a1, Arrow a2, float r) {
		return Arrow(getPos(a1.startPos, a2.startPos, r), getPos(a1.endPos, a2.endPos, r));
	}
}
