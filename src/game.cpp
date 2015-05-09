#include "game.hpp"

//Ctor
Game::Game() {
    graphics = new Graphics;
    board = new Board;
    board->initialize_board();
}

Game::~Game() {
    delete graphics;
    delete board;
}

//Main Game loop. 
void Game::Loop() {
    sf::Event event;
    while (graphics->window_open()) {
        while (graphics->poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                graphics->close_window();
            //Test movement
            } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                board->move_space(0,1, 3,3);
                board->move_space(3,1, 5,3);
            }
        }
        graphics->clear();      //Clear previously drawn screen
        graphics->draw(board);  //Draw, depending in current game state
        graphics->display();    //Show the drawing
    }
}
