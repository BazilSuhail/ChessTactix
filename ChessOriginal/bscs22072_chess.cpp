#include "bscs22072_chess.h"
#include"bscs22072_player.h"
#include"bscs22072_board.h"
#include"bscs22072_piece.h"
#include <fstream>
#include<iostream>

#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#define scl 0.3

chess::chess() {

	ps[0] = new player("WHITE", BLACK);
	ps[1] = new player("BLACK", WHITE);
	Box = new board();
	trn = 1;
}

bool chess::isvalid_source(player* pl, loc S_P)
{
	if (S_P.ri < 0 || S_P.ri >= 8 || S_P.ci < 0 || S_P.ci >= 8)
		return false;
	piece* p = Box->get_piece_at(S_P.ri, S_P.ci);
	return p != nullptr && p->get_clr() == pl->get_clr();
}
bool chess::isvalid_destination(player* AP, loc D_P) {
	return !(isvalid_source(AP, D_P));
}
void chess::dis_trn_mess(RenderWindow& w, int n) {
	sf::Font font;
	if (!font.loadFromFile("Images/phantomstorm.ttf")) {
		cout << "Failed to load font" << endl;
	}
	Text t1("White's Turn", font, 50);
	t1.setPosition(950, 120);
	t1.setFillColor(sf::Color::White);
	Text t2("Black's Turn", font, 50);
	t2.setPosition(950, 650);
	t2.setFillColor(sf::Color::White);
	if (trn == 1) {
		t1.setFillColor(sf::Color::Green);
	}
	else {
		t2.setFillColor(sf::Color::Green);
	}
	w.draw(t1); w.draw(t2);
}
void chess::draw_boxes(RenderWindow& w) {
	Texture S1, S2, S3, S4, back;
	if (!S1.loadFromFile("Images/grey.png") || !S2.loadFromFile("Images/lgrey.png") || !back.loadFromFile("Images/back.png") || !S3.loadFromFile("Images/undo.png") || !S4.loadFromFile("Images/redo.png")) {
		cout << "Failed to load texture!" << endl;
	}
	int daba = S1.getSize().x;
	Sprite b(back);
	b.setPosition(0, 0);
	w.draw(b);
	Sprite sp3(S3);
	sp3.setPosition(1380, 720);
	sp3.setScale(scl, scl);
	w.draw(sp3);
	Sprite sp4(S4);
	sp4.setPosition(1499, 720);
	sp4.setScale(scl, scl);
	w.draw(sp4);
	Sprite sp1(S1);
	Sprite sp2(S2);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) {
				sp1.setPosition(i * daba * scl, j * daba * scl);
				sp1.setScale(scl, scl);
				w.draw(sp1);
			}
			else {
				sp2.setPosition(i * daba * scl, j * daba * scl);
				sp2.setScale(scl, scl);
				w.draw(sp2);
			}
		}
	}
}
void chess::draw_board_pieces(RenderWindow& w, sf::Texture& A) {
	int daba = 345;
	float scale = 0.3;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			loc P;
			P.ri = j; P.ci = i;
			piece* current_piece = Box->get_piece_at(P.ri, P.ci);
			if (current_piece != nullptr) {
				current_piece->board_dis(w, i, j, daba, scale);
			}
		}
	}
}
loc chess::select_src(RenderWindow& window) {
	loc P;
	P = getRowColbyLeftClick(window);
	int br = 101, bc = 101;
	P.ri = P.ri / br;
	P.ci = P.ci / bc;
	return P;
}
void chess::select_undo(RenderWindow& window, Texture& S1, loc S) {
	if (S.ri == 7 && S.ci == 14) {
		Box->redo_undo_game();
		undo_save();
		turn_change();
		draw_boxes(window);					
		dis_trn_mess(window, trn);
		draw_board_pieces(window, S1);		
		window.display();
		S = select_src(window);

		if (S.ri == 7 && S.ci == 15) {
			Box->load_game();
			undo_save();					
			turn_change();
			draw_boxes(window);				
			dis_trn_mess(window, trn);
			draw_board_pieces(window, S1);
			window.display();
			S = select_src(window);
		}
		else
			save();
	}
}
bool** chess::bool_highlight(loc P, int trn) {
	bool** H;
	H = new bool* [8];
	for (int r = 0; r < 8; r++)
		H[r] = new bool[8] {};
	loc D;
	for (int ri = 0; ri < 8; ri++) {
		for (int ci = 0; ci < 8; ci++) {
			D.ri = ri;
			D.ci = ci;
			if (isvalid_destination(ps[trn], D) && Box->get_piece_at(P.ri, P.ci) != nullptr && Box->get_piece_at(P.ri, P.ci)->move_legality(des, Box, P.ri, P.ci, D.ri, D.ci)) {
				Box->load_game();
				move_fake(*Box, P, D);
				H[ri][ci] = (!(apna_check(P, D)));
				Box->load_game();
			}
		}
	}
	Box->load_game();
	return H;
}
void chess::actual_highlight(sf::RenderWindow& w, bool** Box, int Turn, sf::Texture& A) {
	Texture t1;
	if (!t1.loadFromFile("Images/highlight.png")) {
		cout << "Failed to load texture!" << endl;
	}
	Font font;
	if (!font.loadFromFile("Images/phantomstorm.ttf")) {
		cout << "Failed to load font!" << std::endl;
	}
	int daba = A.getSize().x;
	float scale = 0.3;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Box[j][i] == 1) {
				Sprite sp(t1);
				float x = i * daba * scale + daba * scale / 2.0;
				float y = j * daba * scale + daba * scale / 2.0;
				sp.setPosition(x, y);
				sp.setScale(scale, scale);
				sp.setOrigin(sp.getLocalBounds().width / 2.0, sp.getLocalBounds().height / 2.0);
				w.draw(sp);
			}
		}
	}
}
void chess::DisplayCheck(RenderWindow& w){
	sf::Font fnt;
	if (!fnt.loadFromFile("Images/phantomstorm.ttf")) {
		cout << "Failed to load font" << endl;
	}
	Text t("", fnt, 30);
	t.setPosition(950, 320);
	t.setFillColor(sf::Color::Red);
	trn = (trn + 1) % 2;
	trn = (trn + 1) % 2;
	t.setString("Check !!! " + ps[trn]->get_naam() + " Save Your KIng....");
	w.draw(t);
	Box->save_state();
	trn = (trn + 1) % 2;
	trn = (trn + 1) % 2;
}
void DisplayCheck1(RenderWindow& w){
	sf::Font font;
	if (!font.loadFromFile("Images/BAD GRUNGE.ttf")) {
		cout << "Failed to load font" << endl;
	}
	sf::Text t1("     ", font, 50);
	t1.setPosition(800, 150);
	t1.setFillColor(sf::Color::White);
	w.draw(t1);
}
void chess::DisplayCheckMate(RenderWindow& w){
	sf::Font fnt;
	if (!fnt.loadFromFile("Images/phantomstorm.ttf")) {
		cout << "Failed to load font" << endl;
	}turn_change();
	Text t1(ps[trn]->get_naam() + " Wins...", fnt, 30);
	t1.setPosition(950, 420);
	t1.setFillColor(sf::Color::Green);
	w.draw(t1);
	w.display();
	getRowColbyLeftClick(w);
	exit(1);
}
void chess::DisplayStaleMate(RenderWindow& w) {
	sf::Font font;
	if (!font.loadFromFile("Images/BAD GRUNGE.ttf")) {
		cout << "Failed to load font" << endl;
	}
	sf::Text t1("Draw", font, 50);
	t1.setPosition(800, 150);
	t1.setFillColor(sf::Color::White);
	w.draw(t1);
}
void chess::turn_change() {
	trn = (trn + 1) % 2;}
bool chess::check_mate_over() {
	bool** H;
	turn_change();
	loc sc = king_location(Box, trn);
	H = bool_highlight(sc, trn);
	turn_change();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (H[i][j] == 1)
				return true;
		}
	}
	return false;
}
bool chess::stale_mate_game() {
	turn_change();
	loc P;
	for (int i = 0; i < 8; i++) {
		P.ri = i;
		for (int j = 0; j < 8; j++) {
			P.ci = j;
			if (Box->get_piece_at(P.ri, P.ci) == nullptr)
				continue;
			else if (Box->get_piece_at(P.ri, P.ci)->get_type(P.ri, P.ci) == 1)
				continue;
			else if (isvalid_source(ps[trn], P)) {
				turn_change(); return true;
			}
		}
	}
	bool** H;
	loc sc = king_location(Box, trn);
	H = bool_highlight(sc, trn);
	turn_change();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (H[i][j] == 1)
				return true;
		}
	}
	return false;
}
bool chess::Check(board* NB) {
	turn_change();
	loc Des = king_location(NB, trn);
	turn_change();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			loc Sc; Sc.ci = j; Sc.ri = i;
			if (isvalid_source(ps[trn], Sc)) {
				if ((NB->get_piece_at(Sc.ri, Sc.ci)->move_legality(des, NB, Sc.ri, Sc.ci, Des.ri, Des.ci))) {
					return true;
				}
			}
		}
	}
	return false;
}
void chess::copy(board*& NB) {
	NB = new board;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			loc p;
			p.ri = i; p.ci = j;
			NB->ps[i][j] = Box->get_piece_at(p.ri, p.ci);
		}
	}
}
bool chess::apna_check(loc S, loc D) {
	turn_change();
	bool toReturn = Check(Box);
	turn_change();
	return toReturn;
}
void chess::move_fake(board& NB, loc S_P, loc D_P){
	NB.ps[D_P.ri][D_P.ci] = nullptr;//= nullptr;
	NB.ps[D_P.ri][D_P.ci] = NB.ps[S_P.ri][S_P.ci];
	NB.ps[S_P.ri][S_P.ci] = nullptr;
}
void chess::save() {
	ofstream wrt("bscs22072_save.txt");
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			loc P;
			P.ri = r;
			P.ci = c;
			if (Box->get_piece_at(P.ri, P.ci) == nullptr)
				wrt << "-";
			else
				wrt << Box->get_piece_at(P.ri, P.ci)->get_symbol();
		}
		wrt << endl;
	}
}
bool chess::_castling(loc S, loc D){
	if (Box->get_piece_at(S.ri, S.ci)->get_type(S.ri,S.ci)) {
		int a = abs(S.ci - D.ci);
		P.ri = D.ri;
		P.ci = D.ci;
		if (Box->get_piece_at(P.ri, P.ci) == nullptr){
			P.ri = D.ri;	P.ci = D.ci + 1;{
				if (Box->get_piece_at(P.ri, P.ci) == nullptr){
					P.ci = D.ci - 1;{
						if (Box->get_piece_at(P.ri, P.ci) != nullptr && (Box->get_piece_at(P.ri, P.ci)->get_symbol() == 'r' || Box->get_piece_at(P.ri, P.ci)->get_symbol() == 'R')){
							return a == 2;
						}
					}
				}
			}
		}

	}
	return false;
}
void chess::undo_save() {
	ofstream wrt("undo.txt");
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			loc P;
			P.ri = r;	P.ci = c;
			if (Box->get_piece_at(P.ri, P.ci) == nullptr) {
				wrt << "-";
			}
			else {
				wrt << Box->get_piece_at(P.ri, P.ci)->get_symbol();
			}
		}		wrt << endl;
	}
}
void chess::play(sf::RenderWindow& window) {
	sf::Texture S1;
	if (!S1.loadFromFile("Images/grey.png")) {
		cout << "Failed to load texture!" << std::endl;
	}
	sf::Font fnt;
	if (!fnt.loadFromFile("Images/phantomstorm.ttf")) {
		cout << "Failed to load font" << endl;
	}
	bool** m;
	m = new bool* [8] {};
	for (int x = 0; x < 8; x++) { m[x] = new bool[8]; }
	draw_boxes(window);
	draw_board_pieces(window, S1);
	dis_trn_mess(window, trn);
	window.display();
	loc S, D;
	save();
	while (window.isOpen()) {
		system("cls");
		do {
			do {
				S = select_src(window);
				if (S.ri == 7 && S.ci == 14){
					Box->redo_undo_game();
					undo_save();		turn_change();
					draw_boxes(window);	dis_trn_mess(window, trn);
					draw_board_pieces(window, S1);
					window.display();
					S = select_src(window);
					if (S.ri == 7 && S.ci == 15){
						Box->load_game();
						undo_save();				turn_change();
						draw_boxes(window);
						dis_trn_mess(window, trn);	draw_board_pieces(window, S1);
						window.display();
						S = select_src(window);
					}
					else
						save();
				}
				cout << "Selcted Pieces : " << S.ri << " , " << S.ci << endl;
			} while (!isvalid_source(ps[trn], S));
			window.clear();
			draw_boxes(window);
			m = bool_highlight(S, trn);
			actual_highlight(window, m, trn, S1);
			draw_board_pieces(window, S1);
			dis_trn_mess(window, trn);
			window.display();
			D = select_src(window);
			if (m[D.ri][D.ci] != 1)
			{
				draw_boxes(window);
				draw_board_pieces(window, S1);
				dis_trn_mess(window, trn);
				window.display();
			}
			if (D.ri == 7 && D.ci == 14)
			{
				Box->redo_undo_game();
				draw_boxes(window);
				draw_board_pieces(window, S1);
				window.display();
				undo_save();		turn_change();
				S = select_src(window);
				if (S.ri == 7 && S.ci == 15) {
					Box->load_game();
					draw_boxes(window);
					draw_board_pieces(window, S1);
					window.display();
					undo_save();
					turn_change();
					S = select_src(window);
				}
				else
					save();
			}
			cout << "Destination Pieces : " << D.ri << " , " << D.ci << endl;
		} while ((!_castling(S, D)) && (m[D.ri][D.ci] != 1));
		undo_save();
		if (_castling(S, D))
		{
			Box->update_board(S.ri, S.ci, D.ri, D.ci);
			S.ci = S.ci - 3;
			D.ci = D.ci + 1;
		}
		Box->update_board(S.ri, S.ci, D.ri, D.ci);
		save();
		if (Check(Box))
		{
			if (!check_mate_over())
			{
				draw_boxes(window);
				draw_board_pieces(window, S1);
				dis_trn_mess(window, trn);
				DisplayCheckMate(window);
				window.display();
				P = getRowColbyLeftClick(window);
				window.close();
				exit(1);
			}
			else {
				draw_boxes(window);
				draw_board_pieces(window, S1);
				dis_trn_mess(window, trn);
				DisplayCheck(window);
				window.display();
				getRowColbyLeftClick(window);
			}
		}
		else {
			DisplayCheck1(window), window.display();
		}
		if (!stale_mate_game())
		{
			DisplayStaleMate(window);
			window.display();
		}
		if ((D.ri == 0 && Box->get_piece_at(D.ri, D.ci)->get_symbol() == 'p') ||
			(D.ri == 7 && Box->get_piece_at(D.ri, D.ci)->get_symbol() == 'P'))
		{
			Texture x1;
			if (!x1.loadFromFile("Images/promot.png")) {
				cout << "Failed to load texture!" << endl;
			}
			int daba = x1.getSize().x;
			Sprite b(x1);
			b.setPosition(0, 0);
			window.draw(b);		window.display();
			loc P;
			int n = 1;
			P = select_src(window);
			if (P.ri == 4 && P.ci == 15) {
				n = 3;
			}
			else if (P.ri == 3 && P.ci == 15) {
				n = 1;
			}
			else if (P.ri == 4 && P.ci == 14) {
				n = 2;
			}
			else if (P.ri == 3 && P.ci == 14) {
				n = 4;
			}
			Box->setPiece(D.ri, D.ci, n, trn);
		}
		draw_boxes(window);
		draw_board_pieces(window, S1);
		trn = (trn + 1) % 2;
		dis_trn_mess(window, trn);
		save();
		window.display();
	}
}
void chess::play_load(sf::RenderWindow& window) {
	sf::Texture S1;
	if (!S1.loadFromFile("Images/grey.png")) {
		cout << "Failed to load texture!" << std::endl;
		//return;
	}
	Box->load_game();
	sf::Font fnt;
	if (!fnt.loadFromFile("Images/phantomstorm.ttf")) {
		cout << "Failed to load font" << endl;
	}
	bool** m;
	m = new bool* [8] {};
	for (int x = 0; x < 8; x++) { m[x] = new bool[8]; }
	draw_boxes(window);
	draw_board_pieces(window, S1);
	dis_trn_mess(window, trn);
	window.display();
	loc S, D;
	save();
	while (window.isOpen()) {
		system("cls");
		do {
			do {
				S = select_src(window);
				select_undo(window, S1, S);
				cout << "Selcted Pieces : " << S.ri << " , " << S.ci << endl;
			} while (!isvalid_source(ps[trn], S));
			window.clear();
			draw_boxes(window);
			m = bool_highlight(S, trn);
			actual_highlight(window, m, trn, S1);
			draw_board_pieces(window, S1);	dis_trn_mess(window, trn);
			window.display();
			D = select_src(window);
			if (m[D.ri][D.ci] != 1)
			{
				draw_boxes(window);
				draw_board_pieces(window, S1);
				dis_trn_mess(window, trn);
				window.display();
			}
			select_undo(window, S1, S);
			cout << "Destination Pieces : " << D.ri << " , " << D.ci << endl;//<< des.r << " , " << des.c << endl;
		} while ((!_castling(S, D)) && (m[D.ri][D.ci] != 1));
		undo_save();
		if (_castling(S, D)){
			Box->update_board(S.ri, S.ci, D.ri, D.ci);
			S.ci = S.ci - 3;
			D.ci = D.ci + 1;
		}
		Box->update_board(S.ri, S.ci, D.ri, D.ci);
		save();
		if (Check(Box)){
			if (!check_mate_over()){
				draw_boxes(window);
				draw_board_pieces(window, S1);
				dis_trn_mess(window, trn);
				DisplayCheckMate(window);
				window.display();
				P = getRowColbyLeftClick(window);
				window.close();
				exit(1);
			}
			else {
				draw_boxes(window);
				draw_board_pieces(window, S1);
				dis_trn_mess(window, trn);
				DisplayCheck(window);
				window.display();
				getRowColbyLeftClick(window);
			}
		}
		else {
			DisplayCheck1(window), window.display();
		}
		if (!stale_mate_game())
		{
			DisplayStaleMate(window);
			window.display();
		}
		if ((D.ri == 0 && Box->get_piece_at(D.ri, D.ci)->get_symbol() == 'p') ||
			(D.ri == 7 && Box->get_piece_at(D.ri, D.ci)->get_symbol() == 'P'))
		{
			Texture x1;
			if (!x1.loadFromFile("Images/promot.png")) {
				cout << "Failed to load texture!" << endl;
			}
			int daba = x1.getSize().x;
			Sprite b(x1);
			b.setPosition(0, 0);
			window.draw(b);		window.display();
			loc P;
			int n = 1;
			P = select_src(window);
			if (P.ri == 4 && P.ci == 15) {
				n = 3;
			}
			else if (P.ri == 3 && P.ci == 15) {
				n = 1;
			}
			else if (P.ri == 4 && P.ci == 14) {
				n = 2;
			}
			else if (P.ri == 3 && P.ci == 14) {
				n = 4;
			}
			Box->setPiece(D.ri, D.ci, n, trn);
		}
		draw_boxes(window);
		draw_board_pieces(window, S1);
		trn = (trn + 1) % 2;
		dis_trn_mess(window, trn);
		save();
		window.display();
	}
}
