#pragma once

#include <SFML/Graphics.hpp>
#include "Arrow.h"

namespace animation {
	extern sf::Vector2f getPos(sf::Vector2f pos1, sf::Vector2f pos2, float r);
	
	template<class Obj>
	extern Obj getObj(Obj o1, Obj o2, float r) {
		Obj o = o1;
		o.setPosition(getPos(o1.getPosition(), o2.getPosition(), r));
		return o;
	}

	template<class Obj>
	extern Obj getObj(Obj o1, sf::Vector2f pos1, sf::Vector2f pos2, float r) {
		Obj o = o1;
		o.setPosition(getPos(pos1, pos2, r));
		return o;
	}

	extern Arrow getArrow(Arrow a1, Arrow a2, float r);
}
