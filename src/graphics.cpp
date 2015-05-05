#include "graphics.hpp"

Graphics::Graphics() {
    window_.create(sf::VideoMode(WIDTH, HEIGHT), "Chess");
    for(int i=0;i<BOARDSIZE;i++) {
        if((i%2==0 && (i/8)%2==0) || (i%2==1 && (i/8)%2==1)) {
            board_shapes_[i].setFillColor(sf::Color::White);
        } else {
            board_shapes_[i].setFillColor(sf::Color::Black);
        }
        board_shapes_[i].setPosition((i%SIDESIZE)*SQUARESIZE, (i/SIDESIZE)*SQUARESIZE);
        board_shapes_[i].setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    }

    pawn.setFillColor(sf::Color::Cyan);
    pawn.setSize(sf::Vector2f(SQUARESIZE-3,  SQUARESIZE-3));
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
        //std::cout << board->check_space(i%SIDESIZE, i/SIDESIZE) << std::endl;
        if(board->check_space(i%SIDESIZE, i/SIDESIZE) != NULL) {
            pawn.setPosition((i%SIDESIZE)*SQUARESIZE, (i/SIDESIZE)*SQUARESIZE);
            window_.draw(pawn);
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
