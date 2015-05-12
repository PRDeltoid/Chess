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

void Board::set_space(int x, int y, Piece* piece) {
    spaces[x+y*SIDESIZE].piece_ = piece;
}

void Board::reset_space(int x, int y) {
    spaces[x+y*SIDESIZE].piece_ = NULL;
}

Piece* Board::check_space(int x, int y) {
    return spaces[x+y*SIDESIZE].piece_;
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

bool Board::check_hightlight(int x, int y) {
    return spaces[x+y*SIDESIZE].highlight_;
}

void Board::set_highlight(int x, int y, bool truefalse) {
    spaces[x+y*SIDESIZE].highlight_ = truefalse;

}
