#include "bscs22072_board.h"
#include"bscs22072_king.h"
#include"bscs22072_bishop.h"
#include"bscs22072_pawn.h"
#include"bscs22072_queen.h"
#include"bscs22072_knight.h"
#include"bscs22072_rook.h"
#include"bscs22072_piece.h"
#include <fstream>
#include <windows.h>
#include<iostream>

#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
board::board() {
	ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		ps[r] = new piece * [8];
		for (int c = 0; c < 8; c++) {

			if (r == 1) {
				ps[r][c] = new pawn(r, c, WHITE, this);
			}
			else if (r == 6) {
				ps[r][c] = new pawn(r, c, BLACK, this);
			}
			//rook
			else if ((r == 0 && c == 0) || (r == 0 && c == 7)) {
				ps[r][c] = new rook(r, c, WHITE, this);
			}
			else if ((r == 7 && c == 0) || (r == 7 && c == 7)) {
				ps[r][c] = new rook(r, c, BLACK, this);
			}
			//knight
			else if ((r == 0 && c == 1) || (r == 0 && c == 6)) {
				ps[r][c] = new knight(r, c, WHITE, this);

			}
			else if ((r == 7 && c == 1) || (r == 7 && c == 6)) {
				ps[r][c] = new knight(r, c, BLACK, this);
			}
			//bishop
			else if ((r == 0 && c == 2) || (r == 0 && c == 5)) {
				ps[r][c] = new bishop(r, c, WHITE, this);
			}
			else if ((r == 7 && c == 2) || (r == 7 && c == 5)) {
				ps[r][c] = new bishop(r, c, BLACK, this);
			}
			//king
			else if (r == 0 && c == 3)
			{
				ps[r][c] = new king(r, c, WHITE, this);

			}
			else if (r == 7 && c == 3)
			{
				ps[r][c] = new king(r, c, BLACK, this);
			}
			//queen
			else if (r == 0 && c == 4) {
				ps[r][c] = new queen(r, c, WHITE, this);

			}
			else if (r == 7 && c == 4) {
				ps[r][c] = new queen(r, c, BLACK, this);
			}
			else {
				ps[r][c] = nullptr;
			}
		}
	}/*
	ifstream rdr("bscs22072_init.txt");
	ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		ps[r] = new piece * [8];
		for (int c = 0; c < 8; c++) {
			char ch;
			rdr >> ch;
			switch (ch) {
			case 'P': ps[r][c] = new pawn(r, c, WHITE, this); break;
			case 'p': ps[r][c] = new pawn(r, c, BLACK, this); break;
			case 'R': ps[r][c] = new rook(r, c, WHITE, this); break;
			case 'r': ps[r][c] = new rook(r, c, BLACK, this); break;
			case 'N': ps[r][c] = new knight(r, c, WHITE, this); break;
			case 'n': ps[r][c] = new knight(r, c, BLACK, this); break;
			case 'B': ps[r][c] = new bishop(r, c, WHITE, this); break;
			case 'b': ps[r][c] = new bishop(r, c, BLACK, this); break;
			case 'Q': ps[r][c] = new queen(r, c, WHITE, this); break;
			case 'q': ps[r][c] = new queen(r, c, BLACK, this); break;
			case 'K': ps[r][c] = new king(r, c, WHITE, this); break;
			case 'k': ps[r][c] = new king(r, c, BLACK, this); break;
			case '-': ps[r][c] = nullptr;
			}
		}
	}*/
}

void board::update_board(int sr, int sc, int dr, int dc) {
	piece* store = ps[sr][sc];
	ps[dr][dc] = store;
	ps[sr][sc] = nullptr;
}
void board::set_piece_at(int r, int c, piece* pl) {
	ps[r][c] = pl;
}
piece* board::get_piece_at(int r, int c) {
	return ps[r][c];
}


void board::save_undo() {
	ofstream wrt("undo.txt");
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (ps[r][c] != nullptr) {
				wrt << ps[r][c]->get_symbol();
			}
			else {
				wrt << "-";
			}
		}
		wrt << endl;
	}
}
void board::save_state() {
	ofstream wrt("bscs22072_save.txt");
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (ps[r][c] != nullptr) {
				wrt << ps[r][c]->get_symbol();
			}
			else {
				wrt << "-";
			}
		}
		wrt << endl;
	}
}
void board::load_game() {
	ifstream rdr("bscs22072_save.txt");
	ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		ps[r] = new piece * [8];
		for (int c = 0; c < 8; c++) {
			char ch;
			rdr >> ch;
			switch (ch) {
			case 'P': ps[r][c] = new pawn(r, c, WHITE, this); break;
			case 'p': ps[r][c] = new pawn(r, c, BLACK, this); break;
			case 'R': ps[r][c] = new rook(r, c, WHITE, this); break;
			case 'r': ps[r][c] = new rook(r, c, BLACK, this); break;
			case 'N': ps[r][c] = new knight(r, c, WHITE, this); break;
			case 'n': ps[r][c] = new knight(r, c, BLACK, this); break;
			case 'B': ps[r][c] = new bishop(r, c, WHITE, this); break;
			case 'b': ps[r][c] = new bishop(r, c, BLACK, this); break;
			case 'Q': ps[r][c] = new queen(r, c, WHITE, this); break;
			case 'q': ps[r][c] = new queen(r, c, BLACK, this); break;
			case 'K': ps[r][c] = new king(r, c, WHITE, this); break;
			case 'k': ps[r][c] = new king(r, c, BLACK, this); break;
			case '-': ps[r][c] = nullptr;
			}
		}
	}
}
void board::redo_undo_game() {
	ifstream rdr("undo.txt");
	ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		ps[r] = new piece * [8];
		for (int c = 0; c < 8; c++) {
			char ch;
			rdr >> ch;
			switch (ch) {
			case 'P': ps[r][c] = new pawn(r, c, WHITE, this); break;
			case 'p': ps[r][c] = new pawn(r, c, BLACK, this); break;
			case 'R': ps[r][c] = new rook(r, c, WHITE, this); break;
			case 'r': ps[r][c] = new rook(r, c, BLACK, this); break;
			case 'N': ps[r][c] = new knight(r, c, WHITE, this); break;
			case 'n': ps[r][c] = new knight(r, c, BLACK, this); break;
			case 'B': ps[r][c] = new bishop(r, c, WHITE, this); break;
			case 'b': ps[r][c] = new bishop(r, c, BLACK, this); break;
			case 'Q': ps[r][c] = new queen(r, c, WHITE, this); break;
			case 'q': ps[r][c] = new queen(r, c, BLACK, this); break;
			case 'K': ps[r][c] = new king(r, c, WHITE, this); break;
			case 'k': ps[r][c] = new king(r, c, BLACK, this); break;
			case '-': ps[r][c] = nullptr;
			}
		}
	}
}
void board::setPiece(int ri, int ci, int n, int trn)
{
	if (trn == BLACK) {
		switch (n)
		{
		case  (1):
		{
			ps[ri][ci] = new queen(ri, ci, BLACK, this);
			break;
		}
		case  (2):
		{
			ps[ri][ci] = new rook(ri, ci, BLACK, this);
			break;
		}case  (3):
		{
			ps[ri][ci] = new bishop(ri, ci, BLACK, this);
			break;
		}
		case  (4):
		{
			ps[ri][ci] = new knight(ri, ci, BLACK, this);
			break;
		}
		default:
			ps[ri][ci] = new queen(ri, ci, BLACK, this);
			break;
		}
	}
	else
	{
		switch (n)
		{
		case  (1):
		{
			ps[ri][ci] = new queen(ri, ci, WHITE, this);
			break;
		}
		case  (2):
		{
			ps[ri][ci] = new rook(ri, ci, WHITE, this);
			break;
		}case  (3):
		{
			ps[ri][ci] = new bishop(ri, ci, WHITE, this);
			break;
		}
		case  (4):
		{
			ps[ri][ci] = new knight(ri, ci, WHITE, this);
			break;
		}
		default:
			ps[ri][ci] = new queen(ri, ci, WHITE, this);
			break;
		}
	}
}