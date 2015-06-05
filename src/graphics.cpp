#include "graphics.hpp"

//Ctor
Graphics::Graphics(Game* game) {
    window_ = game->get_window();
    board_  = game->get_board();
    highlighter_ = game->get_highlighter();
    outliner_ = game->get_outliner();
    piece_graphics_ = new gfxPiece(SQUARESIZE);
    initialize();
}

Graphics::~Graphics() {
    delete piece_graphics_;
}

//Load piece graphics. 
//Create the board pieces (not the chess pieces, the board squares)
//Clip the chess piece sprites from the spritesheet
//Setup highlight graphic
//Setup Outline graphic
void Graphics::initialize() {
    sf::Color black(136, 0, 12); //Alternative black.
    for(int i=0;i<BOARDSIZE;i++) {
        if((i%2==0 && (i/8)%2==0) || (i%2==1 && (i/8)%2==1)) {
            board_shapes_[i].setFillColor(sf::Color::White);
        } else {
            board_shapes_[i].setFillColor(black);
        }
        board_shapes_[i].setPosition((i%SIDESIZE)*SQUARESIZE, (i/SIDESIZE)*SQUARESIZE);
        board_shapes_[i].setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    }

    create_highlight_gfx();
    create_outline_gfx();
}

//make the highlight square
void Graphics::create_highlight_gfx() {
    sf::Color highlight_color(255, 255, 0, 150);
    highlight_.setFillColor(highlight_color);
    highlight_.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
}

//make the outline square
void Graphics::create_outline_gfx() {
    sf::Color outline_color(255, 0, 0);
    outline_.setFillColor(sf::Color::Transparent);
    outline_.setOutlineThickness(static_cast<float>(OUTLINEWIDTH));
    outline_.setOutlineColor(outline_color);
    outline_.setSize(sf::Vector2f(SQUARESIZE-(OUTLINEWIDTH*2), SQUARESIZE-(OUTLINEWIDTH*2)));

}
//Draw a highlight over position x and y
void Graphics::highlight_square(int x, int y) {
    //Move the highlight into position
    highlight_.setPosition((x)*SQUARESIZE, (y)*SQUARESIZE);
    //Draw the highlighted square
    window_->draw(highlight_);
}

//Draw a outline over position x and y
void Graphics::outline_square(int x, int y) {
    outline_.setPosition((x)*SQUARESIZE+OUTLINEWIDTH, (y)*SQUARESIZE+OUTLINEWIDTH);
    window_->draw(outline_);
}

//Loop through the board and draw all the squares.
//If a square has a piece, render the piece. 
//If a square has highlight/outline, render that.
void Graphics::draw() {
    for(int i=0;i<BOARDSIZE;i++) {
        int x = i%SIDESIZE; //Get the x coordinate for the space to draw
        int y = i/SIDESIZE; //Get the y coordinate for the space to draw
        window_->draw(board_shapes_[i]); //Draw the board background

        if(board_->check_space(x, y) != 0) {
            Piece* piece = board_->check_space(x, y);
            sf::RectangleShape* piece_shape = piece->get_shape();
            piece_shape->setPosition((x)*SQUARESIZE, (y)*SQUARESIZE);
            window_->draw(*piece_shape);
        }

        //If highlight is true, highlight the square
        if(highlighter_->check_hightlight(x, y) == true)
            highlight_square(x, y);
        if(outliner_->check_outline(x, y) == true)
            outline_square(x, y);
    }
}

//Interface to clear the window.
void Graphics::clear() {
    window_->clear();
}

//Interface to display the window's shapes
void Graphics::display() {
    window_->display();
}

//Encasulating function for clear/draw/display
void Graphics::render() {
    clear();
    draw();
    display();
}

