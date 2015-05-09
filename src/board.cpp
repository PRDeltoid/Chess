#include "board.hpp"

void Board::initialize_board() {
    for(int i=0;i<BOARDSIZE;i++) {
        spaces[i].piece_ = NULL;
    }
    Piece* test_piece = new Piece(king, white);
    set_space(3, 3, test_piece); 
}

void Board::set_space(int x, int y, Piece* piece) {
    spaces[x+y*SIDESIZE].piece_ = piece;
}

void Board::reset_space(int x, int y) {
    spaces[x+y*SIDESIZE].piece_ = NULL;
}

Piece* Board::check_space(int x, int y) {
    return spaces[x+y*SIDESIZE].piece_;
}
