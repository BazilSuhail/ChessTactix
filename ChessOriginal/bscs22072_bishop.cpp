#include "bscs22072_bishop.h"
#include<iostream>
#include"bscs22072_piece.h"
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;
bishop::bishop(int _r, int _c, color _col, board* _b) :piece(_r, _c, _col, _b) {
}
// board_dis function
void bishop::board_dis(RenderWindow& w, int x, int y, int daba, float scale) {
    Texture tex;
    if (C == WHITE) {
        if (!tex.loadFromFile("Images/bwhite.png")) {//....
            return;
        }
    }
    else {
        if (!tex.loadFromFile("Images/bblack.png")) {//....
            return;
        }
    }
    Sprite sp(tex);
    float centerX = x * daba * scale + daba * scale / 2.0;
    float centerY = y * daba * scale + daba * scale / 2.0;
    sp.setPosition(centerX, centerY);
    sp.setScale(scale, scale);
    sp.setOrigin(sp.getLocalBounds().width / 2.0, sp.getLocalBounds().height / 2.0);
    w.draw(sp);
}
bool bishop::get_type(int r, int c)//(Position P)
{
    return false;
}
bool bishop::move_legality(board b, board* Box, int sr, int sc, int dr, int dc) {
    return(diagnol_chk(sr, sc, dr, dc) && ((diagnol_L2R(sr, sc, dr, dc, Box)
        || diagnol_R2L(sr, sc, dr, dc, Box))));
}
char bishop::get_symbol() const {
    return (C == BLACK) ? 'b' : 'B';
}