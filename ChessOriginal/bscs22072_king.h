#pragma once
#include "bscs22072_piece.h"
#include"bscs22072_board.h"

#include<SFML/Graphics.hpp>
using namespace sf;
//using namespace std;
class king :public piece {
public:
	king(int _r, int _c, color c, board* b);
	virtual void board_dis(RenderWindow& w, int x, int y, int squareSize, float scale);
	/*piece_ki_type get_type() const override {
		return KING;
	}*/
	virtual bool get_type(int r, int c) override;
	bool move_legality(board b, board* Box, int sr, int sc, int dr, int dc);
	char get_symbol() const override;
};