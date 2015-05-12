#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include "piece.hpp"
#include "board.hpp"

class Movement {
    public:
        Movement(Board* board) :
            board_(board) {};
        ~Movement() {};
        std::vector<int> get_valid_moves(Piece* piece);
    private:
        Board* board_;
};

#endif
