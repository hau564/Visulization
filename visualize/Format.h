#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

namespace format {
	extern bool format(std::string& s);
	extern bool toInt(std::string s, int& x);
	extern bool toVectorInt(std::string s, std::vector<int>& arr);
	extern std::string toString(int x);
}