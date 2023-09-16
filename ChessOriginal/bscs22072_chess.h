#pragma once
#include"bscs22072_piece.h"
#include"bscs22072_board.h"
#include<SFML/Graphics.hpp>
using namespace sf;
class player;
class piece;
class board;
class chess
{
	loc P;
	int trn;
	player* ps[2];
	board* Box;
	board des;
public:
	chess();
	loc select_src(sf::RenderWindow& window);
	void select_undo(RenderWindow& window, Texture&, loc);
	loc getRowColbyLeftClick(sf::RenderWindow& W)
	{
		sf::Event ev;
		while (1)
		{
			while (W.pollEvent(ev))
			{
				if (ev.type == ev.Closed) {
					W.close();
					exit(0);

				}

				/*sf::Event e;
				while (window.pollEvent(e))
				{
					if (e.type == sf::Event::Closed) {
						music.stop();
						window.close();
						exit(0);
					}
				}*/
				if (ev.type == ev.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					auto po = sf::Mouse::getPosition(W);
					return loc(po.y, po.x);
				}
			}
		}
	}
	void DisplayStaleMate(sf::RenderWindow& w);
	void undo_save();
	void DisplayCheck(sf::RenderWindow& w);
	void DisplayCheckMate(sf::RenderWindow& w);
	bool apna_check(loc S, loc D);
	void play(RenderWindow&);
	void play_load(RenderWindow&);
	void dis_trn_mess(sf::RenderWindow& w, int n);
	void draw_boxes(sf::RenderWindow& window);
	void draw_board_pieces(sf::RenderWindow&, sf::Texture&);
	// validdation
	bool isvalid_source(player* AP, loc S_P);
	bool isvalid_destination(player* AP, loc D_P);
	void save();
	//highlight
	bool** bool_highlight(loc P, int trn);
	void actual_highlight(sf::RenderWindow& w, bool** Box, int Turn, sf::Texture& A);
	void turn_change();
	bool _castling(loc S, loc D);
	bool Check(board* NB);
	void copy(board*& NB);
	//fake move cpopy of board
	void move_fake(board& NB, loc S_P, loc D_P);
	loc king_location(board* NB, int t)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				loc P;
				P.ri = i; P.ci = j;
				if (NB->get_piece_at(P.ri, P.ci) == nullptr)
					continue;
				else if (isvalid_source(ps[t], P) == true)
				{
					if (NB->get_piece_at(P.ri, P.ci)->get_type(P.ri, P.ci) == true)
					{
						return P;
					}
				}

			}
		}

	}
	bool check_mate_over();
	bool stale_mate_game();
};
