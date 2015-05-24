#include "piece.hpp"

Piece::Piece(std::string piece_type, std::string piece_color) {
    if(piece_color == "black")
        piece_color_ = black;
    else
        piece_color_ = white;

    if(piece_type == "king")
        piece_type_ = king;
    else if(piece_type == "queen")
        piece_type_ = queen;
    else if(piece_type == "bishop")
        piece_type_ = bishop;
    else if(piece_type == "knight")
        piece_type_ = knight;
    else if(piece_type == "rook")
        piece_type_ = rook;
    else 
        piece_type_ = pawn;

    has_moved_ = false;
}
