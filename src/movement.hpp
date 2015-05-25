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
        vector<Pos> get_valid_moves(Piece* piece);
        vector<Pos> get_column(Piece* piece);
        vector<Pos> get_row(Piece* piece);
        vector<Pos> get_diag(Piece* piece);
        vector<Pos> get_antidiag(Piece* piece);
        vector<Pos> get_pawn_move(Piece* piece);
        vector<Pos> get_pawn_kill_moves(Pos piece_pos, int move_direction);
        vector<Pos> get_knight_move(Piece* piece);
        vector<Pos> get_king_move(Piece* piece);
        vector<Pos> merge_vector(vector<Pos> vector1, vector<Pos> vector2);
        bool pos_valid(Pos pos);
        bool share_color(Pos piece1, Pos piece2);
        bool add_move(Pos move, Pos piece_pos, vector<Pos>& valid_moves);
        void validate_pos_vector(vector<Pos>& vector);
        void clear_valid_moves();
        bool is_valid_move(Pos pos);
        void move_piece(Pos pos_from, Pos pos_to);
    private:
        Board* board_;
        bool blocked(Pos pos_to_check);
        vector<Pos> valid_moves_;
};

#endif
