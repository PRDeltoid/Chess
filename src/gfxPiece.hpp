#ifndef GFXPIECE_H
#define GFXPIECE_H

#include <SFML\Graphics.hpp>
#include "piece.hpp"


class gfxPiece {
    public:
        gfxPiece(int SQUARESIZE);
        ~gfxPiece();
        void load_spritesheet(std::string filename);
        sf::RectangleShape* find_piece_graphic(TYPE piece_type, COLOR piece_color);
        sf::RectangleShape* clip_piece(int from_left, int from_top);
        void clip_all_pieces();
    private:
        int SQUARESIZE_;
        sf::Texture texture_sheet_;
        sf::Image texture_image_;

        sf::RectangleShape* white_king_;
        sf::RectangleShape* black_king_;

        sf::RectangleShape* white_queen_;
        sf::RectangleShape* black_queen_;

        sf::RectangleShape* white_bishop_;
        sf::RectangleShape* black_bishop_;

        sf::RectangleShape* white_knight_;
        sf::RectangleShape* black_knight_;

        sf::RectangleShape* white_rook_;
        sf::RectangleShape* black_rook_;

        sf::RectangleShape* white_pawn_;
        sf::RectangleShape* black_pawn_;
};

#endif
