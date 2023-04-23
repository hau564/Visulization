#pragma once

#include<SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"

namespace loadFile {
	extern Textbox address;
	extern Button load;
	extern void init();
	extern void get(std::vector<std::string>& strs);
}