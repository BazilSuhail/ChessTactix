#include "bscs22072_player.h"
#include<string>
#include "bscs22072_func.h"
player::player(string _n, color _c) {
	this->naam = _n;
	this->clr = _c;
}
string player::get_naam() {
	return naam;
}
color player::get_clr() {
	return clr;
}