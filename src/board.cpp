#include "board.hpp"

Board::~Board() {
    for(unsigned int i=0; i<pieces.size()-1; i++) {
        delete pieces.at(i);
    }
}

void Board::initialize_board() {
    for(int i=0;i<BOARDSIZE;i++) {
        spaces[i].piece_ = NULL;
        spaces[i].highlight_ = false;
        spaces[i].outline_ = false;
    }
    load_pieces("data");
}

void Board::load_pieces(std::string filename) {
    //Open the data file
    std::ifstream datafile;
    datafile.open(filename.c_str());
    //Read data file if open
    if(datafile.is_open()) {
        Piece* piece;
        int piece_x,
            piece_y;
        std::string piece_color,
                    piece_type;
        while(datafile >> piece_x) {
            datafile >> piece_y;
            datafile >> piece_color;
            datafile >> piece_type;
            //Create the piece after reading
            piece = new Piece(piece_type, piece_color);  
            pieces.push_back(piece);
            //Set up the piece on the board
            set_space(piece_x, piece_y, piece);
        }
    }
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

/*bool Board::check_hightlight(int x, int y) {
    return spaces[x+y*SIDESIZE].highlight_;
}

void Board::set_highlight(int x, int y, bool truefalse) {
    spaces[x+y*SIDESIZE].highlight_ = truefalse;
}

void Board::highlight_valid_moves(vector<Pos> valid_moves) {
    if(valid_moves.size() < 1) {                   //Exit if there are no valid moves to highlight
        std::cout << "No valid moves found" << std::endl;
        return;
    }

    for(unsigned int i=0; i < valid_moves.size()-1; i++) {                   //Loop through the valid_moves vector
        std::cout << "x: " << valid_moves[i].x_ << " y: " << valid_moves[i].y_ << std::endl;
        set_highlight(valid_moves[i].x_, valid_moves[i].y_, true); //highlight all of those spaces on the board
    }
}

void Board::clear_all_highlights() {
    for(int i = 0; i < BOARDSIZE; i++)
        spaces[i].highlight_ = false;
}

bool Board::check_outline(int x, int y) {
    return spaces[x+y*SIDESIZE].outline_;
}

void Board::set_outline(int x, int y, bool truefalse) {
    spaces[x+y*SIDESIZE].outline_ = truefalse;
}

void Board::clear_all_outlines() {
    for(int i = 0; i < BOARDSIZE; i++)
        spaces[i].outline_ = false;
}*/

Space* Board::get_spaces() {
    return spaces;
}

Pos Board::find_clicked_pos(int mouse_x, int mouse_y) {
    Pos pos;
    pos.x_ = mouse_x/100;
    pos.y_ = mouse_y/100;
    return pos;
}
