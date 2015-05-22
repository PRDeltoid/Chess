#include "board.hpp"

Board::~Board() {
    /*for(unsigned int i=0; i<pieces_.size()-1; i++) {
        delete pieces_.at(i);
    }*/
    pieces_.clear();
}

void Board::initialize_board() {
    for(int i=0;i<BOARDSIZE;i++) {
        spaces[i].piece_ = NULL;
        spaces[i].highlight_ = false;
        spaces[i].outline_ = false;
    }
}

void Board::add_piece(Piece* piece) {
    pieces_.push_back(piece);
}

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

void Board::set_space(int x, int y, Piece* piece) {
    spaces[x+y*SIDESIZE].piece_ = piece;
}

void Board::reset_space(int x, int y) {
    spaces[x+y*SIDESIZE].piece_ = NULL;
}

Piece* Board::check_space(int x, int y) {
    return spaces[x+y*SIDESIZE].piece_;
}

bool Board::check_empty(int x, int y) {
    if(spaces[x+y*SIDESIZE].piece_ == NULL) {
        return true;
    } else { 
        return false;
    }
}

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

void Board::set_active_piece(Piece* piece) {
    active_piece_ = piece;
}

Piece* Board::get_active_piece() {
    return active_piece_;
}

Space* Board::get_spaces() {
    return spaces;
}

Pos Board::find_clicked_pos(int mouse_x, int mouse_y) {
    Pos pos;
    pos.x_ = mouse_x/100;
    pos.y_ = mouse_y/100;
    return pos;
}
