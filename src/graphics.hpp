#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML\Graphics.hpp>
#include "board.hpp"
#include "highlight.hpp"
#include "outline.hpp"
#include "window.hpp"
#include "game.hpp"
#include "gfxPiece.cpp"

const int SQUARESIZE = 100;
const int OUTLINEWIDTH = 3;

class Graphics {
    public:
        Graphics(Game* game);
        ~Graphics();
        void initialize();
        void render();
        void create_highlight_gfx();
        void create_outline_gfx();
        void highlight_square(int x, int y);
        void outline_square(int x, int y);
        gfxPiece* piece_graphics_;

    private:
        Window* window_;
        Board* board_;
        Highlight* highlighter_;
        Outline* outliner_;
        void draw();
        void clear();
        void display();
        sf::RectangleShape board_shapes_[BOARDSIZE];

        sf::RectangleShape highlight_;
        sf::RectangleShape outline_;
};

#endif
