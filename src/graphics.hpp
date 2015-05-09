#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML\Graphics.hpp>
#include "board.cpp"
#include <string>

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
        void clip_piece(sf::RectangleShape& piece, int from_left, int from_top);//sf::Rect<int>& clip_rect);
        void load_spritesheet(std::string filename);

    private:
        sf::RenderWindow window_;
        sf::RectangleShape board_shapes_[BOARDSIZE];
        sf::RectangleShape white_king_;
        sf::RectangleShape white_queen_;
        sf::Texture texture_sheet_;
        sf::Image texture_image_;
};

#endif
