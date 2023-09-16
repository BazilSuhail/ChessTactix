#pragma once
class piece;
class board {

	//protected:
public:
	piece*** ps;
	board();

	void update_board(int, int, int, int);
	void setPiece(int r, int c, int n, int trn);
	piece* get_piece_at(int r, int c);
	void set_piece_at(int, int, piece*);
	void save_state();
	void load_game();
	void save_undo();
	void redo_undo_game();
};