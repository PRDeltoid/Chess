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
        case bishop:
            valid_moves = merge_vector(get_diag(piece), get_antidiag(piece));
            break;
        case queen:
            valid_moves = merge_vector(merge_vector(get_column(piece), get_row(piece)), merge_vector(get_diag(piece), get_antidiag(piece)));
            break;
        case knight:
            valid_moves = get_knight_move(piece);
        default:
            break;
    };
    return valid_moves;
}

vector<Pos> Movement::get_column(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);  //Find the piece to get the current column of
    vector<Pos> valid_moves;                        //Create a valid moves vector
    for(int i = 0; i < SIDESIZE; i++) {             //Move through the current piece's row. 
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
    for(int i = 0; i < SIDESIZE; i++) {
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

vector<Pos> Movement::get_diag(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move;
        move.x_ = piece_pos.x_+i;
        move.y_ = piece_pos.y_+i;
        valid_moves.push_back(move);
    }
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move;
        move.x_ = piece_pos.x_-i;
        move.y_ = piece_pos.y_-i;
        valid_moves.push_back(move);
    }
    validate_pos_vector(valid_moves);
    return valid_moves;
} 

vector<Pos> Movement::get_antidiag(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move;
        move.x_ = piece_pos.x_+i;
        move.y_ = piece_pos.y_-i;
        if(!pos_valid(move)) {
            break;
        }
        valid_moves.push_back(move);
    }
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move;
        move.x_ = piece_pos.x_-i;
        move.y_ = piece_pos.y_+i;
        if(pos_valid(move)) {
            valid_moves.push_back(move);
        }
    }
    return valid_moves;
}

vector<Pos> Movement::get_pawn_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move_pos;
    int move_distance,
        move_direction = 1;
    //Determine the move distance
    if(piece->has_moved())
        move_distance = 1;
     else 
        move_distance = 2;
     //Determine is the move goes up or down
    if(piece->get_color() == black)
        move_direction = -1;
    //Get the moves needed
    for(int i=1; i <= move_distance; i++) {
        move_pos.y_ = piece_pos.y_ + (i*move_direction);
        move_pos.x_ = piece_pos.x_;
        valid_moves.push_back(move_pos);
    }
    validate_pos_vector(valid_moves);
    return valid_moves;
}

vector<Pos> Movement::get_knight_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move;
    move.x_ = piece_pos.x_ + 2;
    move.y_ = piece_pos.y_ + 1;
    valid_moves.push_back(move);

    move.x_ = piece_pos.x_ - 2;
    move.y_ = piece_pos.y_ - 1;
    valid_moves.push_back(move);
    
    move.x_ = piece_pos.x_ + 1;
    move.y_ = piece_pos.y_ + 2;
    valid_moves.push_back(move);
    
    move.x_ = piece_pos.x_ - 1;
    move.y_ = piece_pos.y_ - 2;
    valid_moves.push_back(move);

    move.x_ = piece_pos.x_ - 2;
    move.y_ = piece_pos.y_ + 1;
    valid_moves.push_back(move);

    move.x_ = piece_pos.x_ - 1;
    move.y_ = piece_pos.y_ + 2;
    valid_moves.push_back(move);

    move.x_ = piece_pos.x_ + 1;
    move.y_ = piece_pos.y_ - 2;
    valid_moves.push_back(move);

    move.x_ = piece_pos.x_ + 2;
    move.y_ = piece_pos.y_ - 1;
    valid_moves.push_back(move);

    validate_pos_vector(valid_moves);
    return valid_moves;
}

vector<Pos> Movement::get_king_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move;
    move.x_ = piece_pos.x_ + 1;
    move.y_ = piece_pos.y_ + 1;
    if(pos_valid(move)) {
        valid_moves.push_back(move);
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

bool Movement::pos_valid(Pos pos) {
    if(pos.x_ > SIDESIZE-1 || 
       pos.y_ > SIDESIZE-1 ||
       pos.x_ < 0 ||
       pos.y_ < 0)
        return false;
    else
        return true;
}

void Movement::validate_pos_vector(vector<Pos>& vector) {
    for(unsigned int i=0; i<vector.size()-1; i++) {
        if(!pos_valid(vector.at(i))) {
            std::cout << "Invalid" << std::endl;
            vector.erase(vector.begin()+i);
        }
    }
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
