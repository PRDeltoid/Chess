#ifndef BOARD_H
#define BOARD_H

#include "pos.hpp"
#include "piece.cpp"
#include <iostream>
#include <fstream>
#include <vector>

struct Space {
    Piece* piece_;
    bool highlight_;
    bool outline_;
};

const int SIDESIZE = 8;
const int BOARDSIZE = SIDESIZE*SIDESIZE;

class Board {
    public:
        Board() {};
        ~Board();
        void initialize_board();
        void load_pieces(std::string filename);
        Pos find_piece_pos(Piece* piece);
        void set_space(int x, int y, Piece* piece);
        void reset_space(int x, int y);
        Piece* check_space(int x, int y);
        void move_space(int x_from, int y_from, int x_to, int y_to);
        void set_active_piece(Piece* piece);
        Piece* get_active_piece();
        bool check_hightlight(int x, int y);
        void set_highlight(int x, int y, bool truefalse);
        void clear_all_highlights();
        bool check_outline(int x, int y);
        void set_outline(int x, int y, bool truefalse);
        void clear_all_outlines();

        Pos find_clicked_pos(int mouse_x, int mouse_y);
    private:
        Space spaces[BOARDSIZE];
        std::vector<Piece*> pieces;
        Piece* active_piece_;
};

#endif
