#ifndef BOARD_H
#define BOARD_H

#include "piece.hpp"
#include <iostream>

struct Space {
    Piece* piece_;
};

const int SIDESIZE = 8;
const int BOARDSIZE = SIDESIZE*SIDESIZE;

class Board {
    public:
        Board() {};
        ~Board() {};
        void initialize_board();
        void set_space(int x, int y, Piece* piece);
        void reset_space(int x, int y);
        Piece* check_space(int x, int y);
    private:
        Space spaces[BOARDSIZE];
};

#endif
