#ifndef BOARD_H
#define BOARD_H

#include "piece.cpp"
#include <iostream>
#include <fstream>
#include <vector>

struct Space {
    Piece* piece_;
};

const int SIDESIZE = 8;
const int BOARDSIZE = SIDESIZE*SIDESIZE;

class Board {
    public:
        Board() {};
        ~Board();
        void initialize_board();
        void load_pieces(std::string filename);
        void set_space(int x, int y, Piece* piece);
        void reset_space(int x, int y);
        Piece* check_space(int x, int y);
        void move_space(int x_from, int y_from, int x_to, int y_to);
    private:
        Space spaces[BOARDSIZE];
        std::vector<Piece*> pieces;
};

#endif
