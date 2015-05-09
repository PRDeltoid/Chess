#include "game.hpp"

//Ctor
Game::Game() {
    graphics = new Graphics;
    board = new Board;
    board->initialize_board();

    Piece* test_piece = new Piece(pawn);
    board->set_space(3, 3, test_piece); 
}

//Main Game loop. 
void Game::Loop() {
    sf::Event event;
    while (graphics->window_open()) {
        while (graphics->poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                graphics->close_window();
            }
        }
        graphics->clear();   //Clear previously drawn screen
        graphics->draw(board);   //Draw, depending in current game state
        graphics->display();   //Show the drawing
    }
}
