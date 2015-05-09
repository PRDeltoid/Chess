#include "board.hpp"

Board::~Board() {
    for(unsigned int i=0; i<pieces.size()-1; i++) {
        delete pieces.at(i);
    }
}

void Board::initialize_board() {
    for(int i=0;i<BOARDSIZE;i++) {
        spaces[i].piece_ = NULL;
    }

    Piece* white_king = new Piece(king, white);
    Piece* black_king = new Piece(king, black);
    pieces.push_back(white_king);
    pieces.push_back(black_king);

    Piece* white_queen = new Piece(queen, white);
    Piece* black_queen = new Piece(queen, black);
    pieces.push_back(white_queen);
    pieces.push_back(black_queen);

    Piece* white_rook = new Piece(rook, white);
    Piece* black_rook = new Piece(rook, black);
    pieces.push_back(white_rook);
    pieces.push_back(black_rook);
    
    Piece* white_bishop = new Piece(bishop, white);
    Piece* black_bishop = new Piece(bishop, black);
    pieces.push_back(white_bishop);
    pieces.push_back(black_bishop);

    Piece* white_knight = new Piece(knight, white);
    Piece* black_knight = new Piece(knight, black);
    pieces.push_back(white_knight);
    pieces.push_back(black_knight);

    Piece* white_pawn = new Piece(pawn, white);
    Piece* black_pawn = new Piece(pawn, black);
    pieces.push_back(white_pawn);
    pieces.push_back(black_pawn);

    set_space(0, 0, white_rook);
    set_space(1, 0, white_knight);
    set_space(2, 0, white_bishop);
    set_space(3, 0, white_queen);
    set_space(4, 0, white_king); 
    set_space(5, 0, white_bishop);
    set_space(6, 0, white_knight);
    set_space(7, 0, white_rook);
    set_space(0, 1, white_pawn);
    set_space(1, 1, white_pawn);
    set_space(2, 1, white_pawn);
    set_space(3, 1, white_pawn);
    set_space(4, 1, white_pawn);
    set_space(5, 1, white_pawn);
    set_space(6, 1, white_pawn);
    set_space(7, 1, white_pawn);

    set_space(0, 7, black_rook);
    set_space(1, 7, black_knight);
    set_space(2, 7, black_bishop);
    set_space(3, 7, black_queen);
    set_space(4, 7, black_king); 
    set_space(5, 7, black_bishop);
    set_space(6, 7, black_knight);
    set_space(7, 7, black_rook);
    set_space(0, 6, black_pawn);
    set_space(1, 6, black_pawn);
    set_space(2, 6, black_pawn);
    set_space(3, 6, black_pawn);
    set_space(4, 6, black_pawn);
    set_space(5, 6, black_pawn);
    set_space(6, 6, black_pawn);
    set_space(7, 6, black_pawn);
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
        std::cout << "Piece being moved" << std::endl;
        //Move it
        set_space(x_to, y_to, moving_piece);
        //Clean up afterwards
        reset_space(x_from, y_from);
    }
}
