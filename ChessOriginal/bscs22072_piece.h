#pragma once
#include<iostream>
#include"bscs22072_func.h"

#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class board;
class piece {
protected:
	int r, ci;
	color C;
	board* b;
	bool moved_status = false;
public:
	piece(int, int, color, board* b);
	virtual void board_dis(RenderWindow& w, int x, int y, int squareSize, float scale) = 0;
	bool is_my_piece(int r, int c, color playerColor);
	virtual bool get_type(int, int) = 0;

	virtual char get_symbol() const = 0;
	void mov_ment(int r, int c);
	color get_clr();

	virtual bool move_legality(board b, board* Box, int sr, int sc, int dr, int dc) = 0;
	// Function to check if a piece has moved
	bool get_moved() {
		return moved_status;
	}

	// Function to set the moved status of a piece
	void moved() {
		moved_status = true;
	}
	bool Move_for_knight_(int sr, int sc, int dr, int dc);
	bool ver_chk_up(int sr, int sc, int dr, int dc);
	bool ver_chk_low(int sr, int sc, int dr, int dc);
	bool hor_path_clear(int sr, int sc, int dr, int dc, board* b);
	bool ver_path_clear(int sr, int sc, int dr, int dc, board* b);
	bool diagnol_L2R(int sr, int sc, int dr, int dc, board* b);
	bool diagnol_R2L(int sr, int sc, int dr, int dc, board* b);
	bool hor_chk(int sr, int sc, int dr, int dc);
	bool diagnol_chk(int sr, int sc, int dr, int dc);
	bool ver_chk(int sr, int sc, int dr, int dc);
};