#include <fstream>
#include"bscs22072_piece.h"
#include<iostream>
#include"bscs22072_board.h"
#include<SFML/Graphics.hpp>
using namespace sf;

using namespace std;
piece::piece(int _r, int _c, color colr, board* box) {
	this->r = _r;
	(*this).ci = _c;
	this->C = colr;
	this->b = box;
}
void piece::mov_ment(int _r, int _c) {
	this->r = _r;
	(*this).ci = _c;
}
color piece::get_clr() {
	return C;
}
bool piece::is_my_piece(int r, int c, color playerColor) {
	piece* p = b->get_piece_at(r, c);
	if (p == nullptr) {
		return false; // there is no piece at the given position
	}
	return p->get_clr() == playerColor;
}
bool piece::hor_chk(int sr, int sc, int dr, int dc)
{
	return (sr == dr);
}
bool piece::diagnol_chk(int sr, int sc, int dr, int dc)
{
	int delta_r = abs(sr - dr);
	int delta_c = abs(sc - dc);
	return (delta_r == delta_c);

}
bool piece::ver_chk(int sr, int sc, int dr, int dc)
{
	return (sc == dc);
}

bool piece::ver_chk_up(int sr, int sc, int dr, int dc)
{
	if (dc == sc && dr > sr)
	{
		return true;
	}
	return false;
}
bool piece::ver_chk_low(int sr, int sc, int dr, int dc)
{
	if (dc == sc && dr < sr)
	{
		return true;
	}
	return false;

}
bool piece::hor_path_clear(int sr, int sc, int dr, int dc, board* b)
{
	int st = min(sc, dc);
	int et = max(sc, dc);
	for (int i = st + 1; i < et; i++) {
		if ((b->get_piece_at(sr, i) != nullptr))
			return false;
	}
	return true;

}
bool piece::ver_path_clear(int sr, int sc, int dr, int dc, board* b)
{
	int st = min(sr, dr);
	int et = max(sr, dr);
	for (int i = st + 1; i < et; i++) {
		if (b->get_piece_at(i, sc) != nullptr)
			return false;
	}
	return true;
}
bool piece::diagnol_L2R(int sr, int sc, int dr, int dc, board* b)
{

	if (dr > sr && dc > sc)
	{
		int a = dr - sr;
		for (int i = 1; i < a; i++)
		{
			loc P;
			P.ci = sc + i;
			P.ri = sr + i;
			if (b->get_piece_at(P.ri,P.ci) == nullptr)
			{
				continue;
				//return false;
			}
			else
				return false;
		}
		return true;
	}
	else if (dr < sr && dc < sc)
	{
		int a = sr - dr;
		for (int i = 1; i < a; i++)
		{
			loc P;
			P.ci = sc - i;
			P.ri = sr - i;
			if (b->get_piece_at(P.ri, P.ci) != nullptr)
			{
				return false;
			}
		}return true;
	}
	return false;

}
bool piece::diagnol_R2L(int sr, int sc, int dr, int dc, board* b)
{

	if (dr > sr && sc > dc)
	{
		int a = dr - sr;
		for (int i = 1; i < a; i++)
		{
			loc P;
			P.ci = sc - i;
			P.ri = sr + i;
			if (b->get_piece_at(P.ri, P.ci) != nullptr)
			{
				return false;
			}
		}return true;
	}
	else if (dr < sr && sc < dc)
	{
		int a = sr - dr;
		for (int i = 1; i < a; i++)
		{
			loc P;
			P.ci = sc + i;
			P.ri = sr - i;
			if (b->get_piece_at(P.ri, P.ci) != nullptr)
			{
				return false;
			}
		}return true;
	}
	return false;

}
bool piece::Move_for_knight_(int sr, int sc, int dr, int dc)
{
	int Dr = abs(dr - sr);
	int Dc = abs(dc - sc);
	return (Dr != Dc);

}