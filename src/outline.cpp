#include "outline.hpp"

Outline::Outline(Board* board) {
    board_ = board;
    spaces_ = board_->get_spaces();
}

bool Outline::check_outline(int x, int y) {
    return spaces_[x+y*SIDESIZE].outline_;
}

void Outline::set_outline(int x, int y, bool truefalse) {
    spaces_[x+y*SIDESIZE].outline_ = truefalse;
}

void Outline::clear_all_outlines() {
    for(int i = 0; i < BOARDSIZE; i++)
        spaces_[i].outline_ = false;
}

