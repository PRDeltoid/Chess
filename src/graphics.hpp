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

    private:
        sf::RenderWindow window_;
        sf::RectangleShape board_shapes_[BOARDSIZE];
        sf::RectangleShape pawn;
};

#endif
