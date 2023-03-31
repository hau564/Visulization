#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

#include "Button.h"
#include "ButtonImage.h"
#include "Slider.h"

namespace control {
	extern ButtonImage play;
	extern ButtonImage nextStep, prevStep;
	extern ButtonImage toEnd, toStart;
	extern Slider speed;

	extern void init();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void draw(sf::RenderWindow& window);
}