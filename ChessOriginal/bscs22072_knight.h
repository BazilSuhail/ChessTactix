#pragma once
#include "bscs22072_piece.h"
#include"bscs22072_board.h"

#include<SFML/Graphics.hpp>
using namespace sf;
class knight :public piece {
public:
	knight(int _r, int _c, color c, board* b);
	virtual void board_dis(RenderWindow& w, int x, int y, int squareSize, float scale);
	/*piece_ki_type get_type() const override {
		return KNIGHT;
	}*/
	virtual bool get_type(int r, int c) override;

	bool move_legality(board Box, board* b, int sr, int sc, int dr, int dc);
	char get_symbol() const override;
};