#pragma once
#include<string>
#include "bscs22072_func.h"

#include<SFML/Graphics.hpp>
using namespace sf;
class player {
	string naam;
	color clr;
public:
	player(string n, color c);
	string get_naam();
	color get_clr();
};
