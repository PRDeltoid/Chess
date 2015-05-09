#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML\Graphics.hpp>
#include "board.cpp"

const int WIDTH = 800;
const int HEIGHT = 800;
const int SQUARESIZE = 100;

class Graphics {
    public:
        Graphics();
        ~Graphics() {}
        void initialize();
        bool window_open();
        void draw(Board* board);
        void clear();
        void display();
        void close_window();
        bool poll_event(sf::Event& event);
        void clip_piece(sf::RectangleShape& piece, int from_left, int from_top);
        void clip_all_pieces();
        void load_spritesheet(std::string filename);
        sf::RectangleShape find_piece_graphic(TYPE piece_type, COLOR piece_color);

    private:
        sf::RenderWindow window_;
        sf::RectangleShape board_shapes_[BOARDSIZE];
        sf::Texture texture_sheet_;
        sf::Image texture_image_;

        sf::RectangleShape white_king_;
        sf::RectangleShape black_king_;

        sf::RectangleShape white_queen_;
        sf::RectangleShape black_queen_;

        sf::RectangleShape white_bishop_;
        sf::RectangleShape black_bishop_;

        sf::RectangleShape white_knight_;
        sf::RectangleShape black_knight_;

        sf::RectangleShape white_rook_;
        sf::RectangleShape black_rook_;

        sf::RectangleShape white_pawn_;
        sf::RectangleShape black_pawn_;
};

#endif
