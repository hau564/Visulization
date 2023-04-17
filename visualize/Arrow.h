#pragma once

#include<SFML/Graphics.hpp>
#include "Layout.h"

class Arrow {
public:
	Arrow();
	Arrow(sf::Vector2f pos1, sf::Vector2f pos2, int k = 0);
	template<class Obj1, class Obj2>
	Arrow(Obj1 o1, Obj2 o2);

	sf::Vector2f startPos, endPos;

	template<class Obj1, class Obj2>
	void create(Obj1 o1, Obj2 o2);

	int id = 0, inited = 0;
	void init();
	void create(sf::Vector2f pos1, sf::Vector2f pos2, int k = 0);
	void draw(sf::RenderWindow& window);

	sf::Sprite s[4];
};

template<class Obj1, class Obj2>
Arrow::Arrow(Obj1 o1, Obj2 o2) {
	float x = layout::display::arrayBlockSize.x / 2.0;
	sf::Vector2f pos1 = o1.getPosition() + sf::Vector2f(x, x);
	sf::Vector2f pos2 = o2.getPosition() + sf::Vector2f(x, x);

	if (abs(pos1.x - pos2.x) < 0.01 && abs(pos1.y - pos2.y) < 0.01)
		create(o1.getPosition(), o1.getPosition());
	else
		create(pos1, pos2, x);
}

template<class Obj1, class Obj2>
void Arrow::create(Obj1 o1, Obj2 o2) {
	float x = layout::display::arrayBlockSize.x / 2.0;
	sf::Vector2f pos1 = o1.getPosition() + sf::Vector2f(x, x);
	sf::Vector2f pos2 = o2.getPosition() + sf::Vector2f(x, x);

	if (abs(pos1.x - pos2.x) < 0.01 && abs(pos1.y - pos2.y) < 0.01)
		create(o1.getPosition(), o1.getPosition());
	else
		create(pos1, pos2, x);
}
