#include "bscs22072_king.h"
#include <fstream>
#include<iostream>
#include"bscs22072_piece.h"
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
king::king(int _r, int _c, color _col, board* _b) :piece(_r, _c, _col, _b) {
}
// board_dis function
void king::board_dis(RenderWindow& w, int x, int y, int squareSize, float scale) {
    Texture tex;
    if (C == WHITE) {
        if (!tex.loadFromFile("Images/kwhite.png")) {//....
            return;
        }
    }
    else {
        if (!tex.loadFromFile("Images/kblack.png")) {//....
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
bool king::get_type(int r, int c)
{
    return true;
}
bool king::move_legality(board b, board* Box, int sr, int sc, int dr, int dc) {

    int delta_r = abs(dr - sr);
    int delta_c = abs(dc - sc);
    if ((delta_r == 1 && delta_c == 0) || (delta_r == 0 && delta_c == 1) || (delta_r == 1 && delta_c == 1)) {
        return ((ver_chk(sr, sc, dr, sc) && ver_path_clear(sr, sc, dr, sc, Box)) || (hor_chk(sr, sc, dr, sc) && hor_path_clear(sr, sc, dr, sc, Box)) ||
            ((diagnol_chk(sr, sc, dr, sc)) && (diagnol_L2R(sr, sc, dr, sc, Box)) || diagnol_R2L(sr, sc, dr, sc, Box)));
    }
    else
        return false;
}
char king::get_symbol() const {
    return (C == BLACK) ? 'k' : 'K';
}