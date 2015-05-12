#include "game.hpp"

//Ctor
Game::Game() {
    board_ = new Board;
    graphics_ = new Graphics(board_);
    movement_ = new Movement(board_);
    board_->initialize_board();
    board_->set_highlight(3, 3, true);
}

Game::~Game() {
    delete graphics_;
    delete board_;
    delete movement_;
}

//Main Game loop. 
void Game::Loop() {
    sf::Event event;
    while (graphics_->window_open()) {
        while (graphics_->poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                graphics_->close_window();
            //Test movement
            } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                board_->move_space(0,1, 3,3);
                board_->move_space(3,1, 5,3);
            }
        }
        graphics_->clear();      //Clear previously drawn screen
        graphics_->draw();  //Draw, depending in current game state
        graphics_->display();    //Show the drawing
    }
}
