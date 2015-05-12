#include "movement.hpp"

vector<Pos> Movement::get_valid_moves(Piece* piece) {
    vector<Pos> valid_moves;
    switch(piece->get_type()) {
        case rook:
            valid_moves = merge_vector(get_column(piece), get_row(piece));
            break;
        default:
            break;
    };
    return valid_moves;
}

void Movement::highlight_valid_moves(vector<Pos> valid_moves) {
    board_->clear_all_highlights();
    for(unsigned int i=0; i < valid_moves.size()-1; i++) 
        board_->set_highlight(valid_moves[i].x_, valid_moves[i].y_, true);
}

vector<Pos> Movement::get_column(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 0; i < SIDESIZE; i++) {
        Pos move;
        move.x_ = piece_pos.x_;
        move.y_ = i;
        valid_moves.push_back(move);
    }
    return valid_moves;
}

vector<Pos> Movement::get_row(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 0; i < SIDESIZE; i++) {
        Pos move;
        move.x_ = i;
        move.y_ = piece_pos.y_;
        valid_moves.push_back(move);
    }
    return valid_moves;
}

//TODO
vector<Pos> Movement::get_diag(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 0; i < BOARDSIZE; i++) {
        Pos move;
        move.x_ = i;
        move.y_ = piece_pos.y_;
    }
    return valid_moves;
} 

//TODO
vector<Pos> Movement::get_antidiag(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 0; i < BOARDSIZE; i++) {
        Pos move;
        move.x_ = i;
        move.y_ = piece_pos.y_;
    }
    return valid_moves;
}

vector<Pos> Movement::merge_vector(vector<Pos> vector1, vector<Pos> vector2) {
    vector<Pos> combined_vector;
    combined_vector.reserve(vector1.size() + vector2.size());
    combined_vector.insert(combined_vector.end(), vector1.begin(), vector1.end());
    combined_vector.insert(combined_vector.end(), vector2.begin(), vector2.end());

    return combined_vector;
}
