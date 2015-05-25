#ifndef PIECE_H
#define PIECE_H

#include <string>

enum TYPE { pawn = 10,   rook = 20,  knight = 30,
            bishop = 40, queen = 50, king = 60 };
enum COLOR { white = 33, black = 66 };

class Piece {
    public:
        Piece(TYPE piece_type, COLOR piece_color) :
            piece_type_(piece_type),
            piece_color_(piece_color),
            has_moved_(false)
        {}
        Piece(std::string piece_type, std::string piece_color);
        virtual ~Piece() {}
        TYPE get_type() { return piece_type_; }
        COLOR get_color() { return piece_color_; }
        bool has_moved() { return has_moved_; }
        void set_moved(bool moved) { has_moved_ = moved; }
    private:
        TYPE piece_type_;
        COLOR piece_color_;
        bool has_moved_;
};

#endif
