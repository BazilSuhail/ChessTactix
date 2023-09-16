#pragma once
#include "bscs22072_piece.h"

#include<SFML/Graphics.hpp>
using namespace sf;
#include"bscs22072_board.h"
//using namespace std;
class pawn :public piece {
public:
	pawn(int _r, int _c, color c, board* b);
	virtual void board_dis(RenderWindow& w, int x, int y, int squareSize, float scale);
	/*piece_ki_type get_type() const override {
		return PAWN;
	}*/

	virtual bool get_type(int r, int c) override;
	char get_symbol() const override;
	bool move_legality(board b, board* Box, int sr, int sc, int dr, int dc);

};