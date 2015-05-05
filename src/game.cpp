#include "game.hpp"

//Ctor
Game::Game() {
    graphics = new Graphics;
    board = new Board;
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
