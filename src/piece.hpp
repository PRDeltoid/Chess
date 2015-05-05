#ifndef PIECE_H
#define PIECE_H

enum TYPE { pawn = 10, rook = 20, knight = 30, bishop = 40, queen = 50, king = 60 };

class Piece {
    public:
        Piece(TYPE piece_type) :
            piece_type_(piece_type)
        {}
        virtual ~Piece() {}
        TYPE get_type() { return piece_type_; }
    private:
        TYPE piece_type_;
};

#endif
