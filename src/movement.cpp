#include "movement.hpp"

//Determine which moves to get determined by piece type
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
    valid_moves_ = valid_moves;
    return valid_moves;
}

//Get the valid columns of spaces from a piece
vector<Pos> Movement::get_column(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);  //Find the piece to get the current column of
    vector<Pos> valid_moves;                        //Create a valid moves vector
   
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_, piece_pos.y_+i);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_, piece_pos.y_-i);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    return valid_moves;                             //Return the valid moves vector
}

//Get the row of spaces from a piece
vector<Pos> Movement::get_row(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_+i, piece_pos.y_);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_-i, piece_pos.y_);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    return valid_moves;
}

//Get the diag spaces from a piece.
vector<Pos> Movement::get_diag(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_+i, piece_pos.y_+i);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_-i, piece_pos.y_-i);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    return valid_moves;
} 

//Get the anti diag spaces from a piece
vector<Pos> Movement::get_antidiag(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_+i, piece_pos.y_-i);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    for(int i = 1; i < SIDESIZE; i++) {
        Pos move(piece_pos.x_-i, piece_pos.y_+i);
        if(add_move(move, piece_pos, valid_moves) == false) 
            break;
    }
    return valid_moves;
}

//Get Pawn valid moves
vector<Pos> Movement::get_pawn_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move_pos;
    int move_distance = 1,
        move_direction = 1;
    //Determine the move distance
    if(!piece->has_moved()) {
        move_distance = 2;
    }
     //Determine is the move goes up or down
    if(piece->get_color() == black)
        move_direction = -1;
    //Get the moves needed
    for(int i=1; i <= move_distance; i++) {
        move_pos.y_ = piece_pos.y_ + (i*move_direction);
        move_pos.x_ = piece_pos.x_;
        if(blocked(move_pos))
            break;
        if(pos_valid(move_pos) && !blocked(move_pos))
            valid_moves.push_back(move_pos);
    }

    vector<Pos> kill_moves = get_pawn_kill_moves(piece_pos, move_direction);
    valid_moves = merge_vector(valid_moves, kill_moves);
    validate_pos_vector(valid_moves);
    return valid_moves;
}

vector<Pos> Movement::get_pawn_kill_moves(Pos piece_pos, int move_direction) {
    Piece* piece1 = board_->check_space(piece_pos.x_ + (1*move_direction), piece_pos.y_ + (1*move_direction));
    Pos piece1_pos = board_-> find_piece_pos(piece1);
    Piece* piece2 = board_->check_space(piece_pos.x_ - (1*move_direction), piece_pos.y_ - (1*move_direction));
    Pos piece2_pos = board_-> find_piece_pos(piece2);
    vector<Pos> kill_moves;
    
    if(piece1 != NULL) {
        if(!share_color(piece_pos, piece1_pos))
            kill_moves.push_back(piece1_pos);
    }
    if(piece2 != NULL) {
        if(!share_color(piece_pos, piece2_pos))
            kill_moves.push_back(piece2_pos);
    }
    return kill_moves;
}

//Get knight valid moves. This piece can jump over other pieces
vector<Pos> Movement::get_knight_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move(piece_pos.x_ + 2, piece_pos.y_ + 1);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);

    move.set_pos(piece_pos.x_ -2, piece_pos.y_ -1);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);
    
    move.set_pos(piece_pos.x_ +1, piece_pos.y_ +2);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);
    
    move.set_pos(piece_pos.x_ -1, piece_pos.y_ -2);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);

    move.set_pos(piece_pos.x_ -2, piece_pos.y_ +1);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);

    move.set_pos(piece_pos.x_ -1, piece_pos.y_ +2);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);

    move.set_pos(piece_pos.x_ +1, piece_pos.y_ -2);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);

    move.set_pos(piece_pos.x_ +2, piece_pos.y_ -1);
    if(!share_color(piece_pos, move)) 
        valid_moves.push_back(move);

    validate_pos_vector(valid_moves);
    return valid_moves;
}

//Get the Kings valid moves
vector<Pos> Movement::get_king_move(Piece* piece) {
    Pos piece_pos = board_->find_piece_pos(piece);
    vector<Pos> valid_moves;
    Pos move(piece_pos.x_+1, piece_pos.y_+1);
    if(pos_valid(move) && !share_color(piece_pos, move)) {
        valid_moves.push_back(move);
    }
    return valid_moves;
}

//Merge two vectors together
vector<Pos> Movement::merge_vector(vector<Pos> vector1, vector<Pos> vector2) {
    vector<Pos> combined_vector;
    combined_vector.reserve(vector1.size() + vector2.size());
    combined_vector.insert(combined_vector.end(), vector1.begin(), vector1.end());
    combined_vector.insert(combined_vector.end(), vector2.begin(), vector2.end());

    return combined_vector;
}

//Check if a position is within the board boundaries.
//Returns true if it is within bounds, false if it is outside
bool Movement::pos_valid(Pos pos) {
    if(pos.x_ > SIDESIZE-1 || 
       pos.y_ > SIDESIZE-1 ||
       pos.x_ < 0 ||
       pos.y_ < 0)
        return false;
    else
        return true;
}

//Checks if the two positions have pieces that share a color.
//Returns true if they share a color, false if they do not (or if there is no piece
//in one of the positions)
bool Movement::share_color(Pos piece1_pos, Pos piece2_pos) {
    Piece* piece1 = board_->check_space(piece1_pos.x_, piece1_pos.y_);
    Piece* piece2 = board_->check_space(piece2_pos.x_, piece2_pos.y_);
    if(piece1 != NULL && piece2 != NULL) {
        if(piece1->get_color() == piece2->get_color()) 
            return true;
        else
            return false;
    }
    return false;
}

//Add a move if the move is within bounds and if there is no piece with a 
//shared color in the destination position. If the move is blocked by an
//opposite colored piece, add the move but return false.
//Returns true if the move was added and it is not the last move to add (if the piece
//isn't blocked. 
//Returns false if the move was blocked, or if the position of the move is invalid
//(shares a color or the position is invalid)
bool Movement::add_move(Pos move, Pos piece_pos, vector<Pos>& valid_moves) {
    if(!pos_valid(move) || share_color(piece_pos, move))
        return false;
    valid_moves.push_back(move);
    if(blocked(move)) 
        return false;

    return true;
}

//Check each Pos in a vector and verify they are within bounds.
//Remove them otherwise
void Movement::validate_pos_vector(vector<Pos>& vector) {
    std::vector<Pos>::iterator itt;
    for(itt = vector.begin(); itt != vector.end(); itt++) {
        //If a position is outside the board, get rid of it
        if(!pos_valid(*itt)) {
            vector.erase(itt);
            //move the itterator back if a pos is deleted
            itt--;
        }
    }
}

//Check if a piece on the board is empty or a piece is blocking
//Returns true is the destination has a piece on it.
//Returns false if the destination is empty
bool Movement::blocked(Pos pos_to_check) {
    int x = pos_to_check.x_;
    int y = pos_to_check.y_;

    if(board_->check_empty(x, y)) {
        return false;
    }
    return true;
}

void Movement::clear_valid_moves() {
    valid_moves_.clear();
}

//Checks if a move is valid (if the position clicked is on
//the valid moves list)
bool Movement::is_valid_move(Pos pos_clicked) {
    //Exit early if there is no valid move list
    if(valid_moves_.size() < 1)
        return false;
    //Loop through all valid moves and compare it to the position clicked
    for(unsigned int i=0; i < valid_moves_.size(); i++) {
        if(valid_moves_[i] == pos_clicked) {
            //If a move is valid, move the piece.
            board_->get_active_piece()->set_moved(true);
            Pos piece_pos = board_->find_piece_pos(board_->get_active_piece());
            move_piece(piece_pos, pos_clicked);
            return true;
        }
    }
    return false;
}

//Moves a piece and sets the active piece to null afterwards.
//Also deletes any piece landed on by the active piece, to prevent memory leaks
void Movement::move_piece(Pos pos_from, Pos pos_to) {
    Piece* dead_piece = board_->check_space(pos_to.x_, pos_to.y_);
    delete dead_piece; //Delete the piece that is about to be killed.
    board_->move_space(pos_from.x_, pos_from.y_, pos_to.x_, pos_to.y_);
    board_->move_space(pos_from, pos_to);
    board_->set_active_piece(NULL); 
}
