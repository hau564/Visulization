#include "Arrow.h"
#include<iostream>

#define PI 3.14159265359

void Arrow::init() {
	for (int i = 0; i < 3; ++i) {
		s[i].setTexture(layout::arrow::t[i]);
	}
}

void Arrow::create(sf::Vector2f pos1, sf::Vector2f pos2, int k) {
	init();
	
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float d = sqrt(dx * dx + dy * dy);
	if (k != 0) {
		float r = 1.0 * k / d;
		create(pos1, sf::Vector2f(pos2.x - r * dx, pos2.y - r * dy));
		return;
	}

	for (int i = 0; i < 3; ++i) {
		sf::FloatRect rect = s[i].getLocalBounds();
		s[i].setOrigin(0, rect.height / 2);

		s[i].setPosition(pos1);
		s[i].setScale(d / layout::arrow::t[i].getSize().x, 1);

		float angle = acos(dx / d) / PI * 180.0;
		if (dy < 0) angle = -angle;
		s[i].rotate(angle);
	}
}

void Arrow::draw(sf::RenderWindow& window) {
	window.draw(s[id]);
}


Arrow::Arrow() {
	init();
}

Arrow::Arrow(sf::Vector2f pos1, sf::Vector2f pos2, int k) {
	create(pos1, pos2, k);
}



