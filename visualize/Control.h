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
	extern void update();

	extern int slideId;
	extern float timePerSlide;
	extern float slideStart, cur;
	extern std::vector<float> slideTime;
	extern std::vector<int> checkpoint;
	
	extern void addSlide(float weight = 1.0);
	extern void addCheckpoint();
	extern void clear();
	extern void start();
	extern int getSlideId();
	extern int getCheckpointId();
}