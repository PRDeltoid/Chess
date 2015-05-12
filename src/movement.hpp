#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include "piece.hpp"
#include "board.hpp"

using std::vector;

class Movement {
    public:
        Movement(Board* board) :
            board_(board) {};
        ~Movement() {};
        std::vector<Pos> get_valid_moves(Piece* piece);
        void highlight_valid_moves(std::vector<Pos> valid_moves);
        std::vector<Pos> get_column(Piece* piece);
        std::vector<Pos> get_row(Piece* piece);
        std::vector<Pos> get_diag(Piece* piece);
        std::vector<Pos> get_antidiag(Piece* piece);
        vector<Pos> merge_vector(vector<Pos> vector1, vector<Pos> vector2);
    private:
        Board* board_;
};

#endif
