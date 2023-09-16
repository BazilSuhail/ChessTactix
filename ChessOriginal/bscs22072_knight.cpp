#include "bscs22072_knight.h"
#include <fstream>
#include<iostream>
#include"bscs22072_piece.h"

#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
knight::knight(int _r, int _c, color _col, board* _b) :piece(_r, _c, _col, _b) {
}
// board_dis function
void knight::board_dis(RenderWindow& w, int x, int y, int squareSize, float scale) {
    Texture tex;
    if (C == WHITE) {
        if (!tex.loadFromFile("Images/nwhite.png")) {//....
            return;
        }
    }
    else {
        if (!tex.loadFromFile("Images/nblack.png")) {//....
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
bool knight::get_type(int r, int c)
{
    return false;
}

bool knight::move_legality(board Box, board* b, int sr, int sc, int dr, int dc)
{
    int delta_r = abs(dr - sr);
    int delta_c = abs(dc - sc);
    if ((delta_r == 2 && delta_c == 1) || (delta_r == 1 && delta_c == 2))
    {
        return Move_for_knight_(sr, sc, dr, dc);
    }

    return false;
}
char knight::get_symbol() const {
    return (C == BLACK) ? 'n' : 'N';
}