#include "graphics.hpp"

Graphics::Graphics() {
    window_.create(sf::VideoMode(WIDTH, HEIGHT), "Chess", sf::Style::Close); //Create an unresizable window
    load_spritesheet("Chess_Pieces_Sprite.bmp"); //Load spritesheet

    //Create the board's shapes (not the pieces).
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

    //Clip the piece sprites. 
    clip_piece(white_king_, 0, 0); //clip_rect);

}

bool Graphics::window_open() {
    return window_.isOpen();
}

void Graphics::display() {
    window_.display();
}

void Graphics::draw(Board* board) {
    for(int i=0;i<BOARDSIZE;i++) {
        window_.draw(board_shapes_[i]);
        if(board->check_space(i%SIDESIZE, i/SIDESIZE) != NULL) {
            if(board->check_space(i%SIDESIZE, i/SIDESIZE)->get_type() == pawn) { 
                white_king_.setPosition((i%SIDESIZE)*SQUARESIZE, (i/SIDESIZE)*SQUARESIZE);
                window_.draw(white_king_);
            }
        }
    }
}

void Graphics::clear() {
    window_.clear();
}

void Graphics::close_window() {
    window_.close();
}

bool Graphics::poll_event(sf::Event& event) {
    return window_.pollEvent(event);
}

void Graphics::clip_piece(sf::RectangleShape& piece, int from_left, int from_top) { // sf::Rect<int>& clip_rect) {
    sf::Rect<int> clip_rect;
    piece.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    clip_rect.height = clip_rect.width = SQUARESIZE;
    clip_rect.top = from_top * SQUARESIZE;
    clip_rect.left = from_left * SQUARESIZE;
    piece.setTexture(&texture_sheet_, false);
    piece.setTextureRect(clip_rect);
}

void Graphics::load_spritesheet(std::string filename) {
    texture_image_.loadFromFile(filename); 
    texture_image_.createMaskFromColor(sf::Color::Green, 0); //Transparency key
    texture_sheet_.loadFromImage(texture_image_);
    texture_sheet_.setSmooth(true); //Smooth edges

}
