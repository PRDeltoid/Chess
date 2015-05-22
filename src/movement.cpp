#include "movement.hpp"

vector<Pos> Movement::get_valid_moves(Piece* piece) {
    vector<Pos> valid_moves;
    //Get the valid moves of the piece depending on the piece type
    switch(piece->get_type()) {
        case rook:
            valid_moves = merge_vector(get_column(piece), get_row(piece));
            break;
        case pawn:
            valid_moves = get_pawn_move(piece);
            break;
        default:
            break;
    };
    return valid_moves;
}

vector<Pos> Movement::get_column(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);  //Find the piece to get the current column of
    vector<Pos> valid_moves;                        //Create a valid moves vector
    for(int i = 0; i <= SIDESIZE; i++) {             //Move through the current piece's row. 
        Pos move;
        //If the current position is the piece, ignore it
        if(i == piece_pos.y_) {
            continue;
        }
        move.x_ = piece_pos.x_;
        move.y_ = i;
        /*if(blocked(move, piece->get_color())) {     //Check if the piece is blocked by a friendly piece 
            return valid_moves;                     //If it's blocked, stop finding new valid moves and return
        }*/
        valid_moves.push_back(move);                //If the piece wasn't blocked, push the valid move into the valid moves vector
    }
    return valid_moves;                             //Return the valid moves vector
}

vector<Pos> Movement::get_row(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 0; i <= SIDESIZE; i++) {
        Pos move;
        if(i == piece_pos.x_) {
            continue;
        }
        move.x_ = i;
        move.y_ = piece_pos.y_;
        /*if(blocked(move, piece->get_color())) {
            return valid_moves;
        }*/
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

vector<Pos> Movement::get_pawn_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move_pos;
    if(piece->get_color() == black) {
        move_pos.y_ = piece_pos.y_ - 1;
        move_pos.x_ = piece_pos.x_;
    } else {
        move_pos.y_ = piece_pos.y_ + 1;
        move_pos.x_ = piece_pos.x_;
    }
    std::cout << move_pos.x_ << " " << move_pos.y_ << std::endl;
    valid_moves.push_back(move_pos);
    return valid_moves;
}

vector<Pos> Movement::merge_vector(vector<Pos> vector1, vector<Pos> vector2) {
    vector<Pos> combined_vector;
    combined_vector.reserve(vector1.size() + vector2.size());
    combined_vector.insert(combined_vector.end(), vector1.begin(), vector1.end());
    combined_vector.insert(combined_vector.end(), vector2.begin(), vector2.end());

    return combined_vector;
}

//TODO
bool Movement::blocked(Pos pos_to_check, COLOR piece_color) {
    int x = pos_to_check.x_;
    int y = pos_to_check.y_;

    if(board_->check_empty(x, y)) {
        if(board_->check_space(x, y)->get_color() == piece_color)
            return true;
    }
    return false;
}
