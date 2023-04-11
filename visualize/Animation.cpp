#include "Animation.h"

namespace animation {
	sf::Vector2f getPos(sf::Vector2f pos1, sf::Vector2f pos2, float r) {
		return { pos1.x + r * (pos2.x - pos1.x) , pos1.y + r * (pos2.y - pos1.y) };
	}

	/*template<class Obj>
	Obj getObj(Obj o1, Obj o2, float r) {
		Obj o = o1;
		o.setPosition(getPos(o1.getPosition(), o2.getPosition(), r));
		return o;
	}

	template<class Obj>
	Obj getObj(Obj o1, sf::Vector2f pos1, sf::Vector2f pos2, float r) {
		Obj o = o1;
		o.setPosition(getPos(pos1, pos2, r));
		return o;
	}*/

	Arrow getArrow(Arrow a1, Arrow a2, float r) {
		return Arrow(getPos(a1.startPos, a2.startPos, r), getPos(a1.endPos, a2.endPos, r));
	}
}
