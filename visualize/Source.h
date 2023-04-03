#pragma once

#include<SFML/Graphics.hpp>

namespace source {
	extern std::vector<sf::Text> texts;
	extern std::vector<sf::RectangleShape> rects;
	extern sf::Font font;
	extern int cnt, hightlightPos, prevFocused, lineCount;
	
	extern void init();
	extern void clear();
	extern void setSource(std::vector<std::string> strs);
		
	extern void hightlight(int pos);
	extern void draw(sf::RenderWindow& window);
}