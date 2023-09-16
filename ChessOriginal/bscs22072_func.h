#include <fstream>
#include<iostream>
using namespace std;
#pragma once
enum color { BLACK, WHITE = 15 };
//enum piece_ki_type { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

class loc {
public:
	int ri;
	int ci;
	loc()
	{
		ri = 0; ci = 0;
	}
	loc(int r, int c) :
		ri{ r }, ci{ c }
	{

	}
};
