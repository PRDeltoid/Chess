#include "board.hpp"

Board::~Board() {
    pieces_.clear();
}

//Set up a blank board
void Board::initialize_board() {
    for(int i=0;i<BOARDSIZE;i++) {
        spaces[i].piece_ = NULL;
        spaces[i].highlight_ = false;
        spaces[i].outline_ = false;
    }
}

//Add a piece to the pieces list.
void Board::add_piece(Piece* piece) {
    pieces_.push_back(piece);
}

//Find a piece's Position on the board
//Returns the position of the piece, if found.
//Otherwise returns -1, -1 for the Position
Pos Board::find_piece_pos(Piece* piece) {
    Pos pos;
    pos.x_ = -1;
    pos.y_ = -1;
    for(int i = 0; i < BOARDSIZE; i++) {
        if(spaces[i].piece_ == piece) {
            pos.x_ = i%SIDESIZE;
            pos.y_ = i/SIDESIZE;
            //return pos; 
            break;
        }
    }
    return pos;
}

//Copy a piece to a space.
void Board::set_space(int x, int y, Piece* piece) {
    spaces[x+y*SIDESIZE].piece_ = piece;
}

//Clear a space of any piece on it
void Board::reset_space(int x, int y) {
    spaces[x+y*SIDESIZE].piece_ = NULL;
}

//Get the space's piece.
//Returns NULL if no piece is found
Piece* Board::check_space(int x, int y) {
    return spaces[x+y*SIDESIZE].piece_;
}

//Check if a space is empty.
//returns true if it is empty
//returns false if it is not empty
bool Board::check_empty(int x, int y) {
    if(spaces[x+y*SIDESIZE].piece_ == NULL) {
        return true;
    } else { 
        return false;
    }
}

//Move a piece from one space to another.
void Board::move_space(int x_from, int y_from, int x_to, int y_to) {
    //Find the piece to move
    Piece* moving_piece = check_space(x_from, y_from);
    if(moving_piece != NULL) {
        //Move it
        set_space(x_to, y_to, moving_piece);
        //Clean up afterwards
        reset_space(x_from, y_from);
    }
}

//Move a piece from one space to another.
void Board::move_space(Pos pos_from, Pos pos_to) {
    //Find the piece to move
    Piece* moving_piece = check_space(pos_from.x_, pos_from.y_);
    if(moving_piece != NULL) {
        //Move it
        set_space(pos_to.x_, pos_to.y_, moving_piece);
        //Clean up afterwards
        reset_space(pos_from.x_, pos_from.y_);
    }
}

//Set a piece to the "active piece,", which can be move
void Board::set_active_piece(Piece* piece) {
    active_piece_ = piece;
}

//Returns the active piece
Piece* Board::get_active_piece() {
    return active_piece_;
}

//Returns the list of spaces on the board
Space* Board::get_spaces() {
    return spaces;
}

//Determine the position on the board using mouse cooridates
Pos Board::find_clicked_pos(int mouse_x, int mouse_y) {
    Pos pos;
    pos.x_ = mouse_x/100;
    pos.y_ = mouse_y/100;
    return pos;
}
