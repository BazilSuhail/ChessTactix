#include"bscs22072_pawn.h"
#include<windows.h>
#include <fstream>
#include<iostream>
#include"bscs22072_piece.h"
#include"bscs22072_board.h"
#include"bscs22072_king.h"
#include"bscs22072_queen.h"

#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
pawn::pawn(int _r, int _c, color _col, board* _b) :piece(_r, _c, _col, _b) {
}
bool pawn::get_type(int r, int c)
{
	return false;
}
char pawn::get_symbol() const {
	return (C == BLACK) ? 'p' : 'P';
}
// board_dis function
void pawn::board_dis(RenderWindow& w, int x, int y, int squareSize, float scale) {
	Texture tex;
	if (C == WHITE) {
		if (!tex.loadFromFile("Images/pwhite.png")) {//....
			return;
		}
	}
	else {
		if (!tex.loadFromFile("Images/pblack.png")) {//....
			return;
		}
	}
	Sprite sp(tex);
	float centerX = x * squareSize * scale + squareSize * scale / 2.0;
	float centerY = y * squareSize * scale + squareSize * scale / 2.0;
	sp.setPosition(centerX, centerY);
	sp.setScale(scale, scale);
	sp.setOrigin(sp.getLocalBounds().width / 2.0, sp.getLocalBounds().height / 2.0);
	w.draw(sp);
}
bool pawn::move_legality(board Box, board* b, int sr, int sc, int dr, int dc) {
	if (C == WHITE)
	{
		if (sr == 1)
		{
			if (dr - sr > 2)
				return false;
			if (dr - sr == 2 && dc - sc == 0)
			{
				return  (b->get_piece_at(dr, dc) == nullptr) && ver_path_clear(sr, sc, dr, dc, b);
			}
			if (dr - sr == 1 && dc - sc == 0)
			{
				return  (b->get_piece_at(dr, dc) == nullptr);
			}
			if (dr - sr == 1 && abs(dc - sc) == 1)
			{
				return  (b->get_piece_at(dr, dc) != nullptr);
			}
		}
		else
		{

			if (dr - sr != 1)
				return false;
			if (dr - sr == 1 && dc - sc == 0)
			{
				return  (b->get_piece_at(dr, dc) == nullptr);
			}
			if (dr - sr == 1 && abs(dc - sc) == 1)
			{
				return  (b->get_piece_at(dr, dc) != nullptr);
			}
		}
	}
	else
	{
		if (sr == 6)
		{
			if (sr - dr > 2)
				return false;
			if (sr - dr == 2 && dc - sc == 0)
			{
				return  (b->get_piece_at(dr, dc) == nullptr) && ver_path_clear(sr, sc, dr, dc, b);
			}
			if (sr - dr == 1 && dc - sc == 0)
			{
				return  (b->get_piece_at(dr, dc) == nullptr);
			}
			if (sr - dr == 1 && abs(dc - sc) == 1)
			{
				return  (b->get_piece_at(dr, dc) != nullptr);
			}
		}
		else
		{
			if (sr - dr != 1)
				return false;
			if (sr - dr == 1 && dc - sc == 0)
			{
				return  (b->get_piece_at(dr, dc) == nullptr);
			}
			if (sr - dr == 1 && abs(dc - sc) == 1)
			{
				return  (b->get_piece_at(dr, dc) != nullptr);
			}
		}
	}
	return false;
}