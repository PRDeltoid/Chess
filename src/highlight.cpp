#include "highlight.hpp"

Highlight::Highlight(Board* board) {
    board_ = board;
    spaces_ = board_->get_spaces();
}

bool Highlight::check_hightlight(int x, int y) {
    return spaces_[x+y*SIDESIZE].highlight_;
}

void Highlight::set_highlight(int x, int y, bool truefalse) {
    spaces_[x+y*SIDESIZE].highlight_ = truefalse;
}

void Highlight::highlight_valid_moves(vector<Pos> valid_moves) {
    if(valid_moves.size() < 1) {                   //Exit if there are no valid moves to highlight
        std::cout << "No valid moves found" << std::endl;
        return;
    }

    for(unsigned int i=0; i < valid_moves.size(); i++) {                   //Loop through the valid_moves vector
        set_highlight(valid_moves[i].x_, valid_moves[i].y_, true); //highlight all of those spaces on the board
    }
}

void Highlight::clear_all_highlights() {
    for(int i = 0; i < BOARDSIZE; i++)
        spaces_[i].highlight_ = false;
}
