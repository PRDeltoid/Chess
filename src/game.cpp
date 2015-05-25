#include "game.hpp"
#include "ui.cpp"

//Ctor
Game::Game() {
    board_       = new Board;
    highlighter_ = new Highlight(board_);
    outliner_    = new Outline(board_);
    graphics_    = new Graphics(board_, highlighter_, outliner_);
    movement_    = new Movement(board_);
    dataloader_  = new DataLoader(board_);
    ui_          = new UI(this);
    board_->initialize_board();
    dataloader_->load_pieces("data/piecedata");
    active_player = white;
}

//Dtor
Game::~Game() {
    delete graphics_;
    delete board_;
    delete movement_;
    delete highlighter_;
    delete outliner_;
    delete dataloader_;
}

//Switch the active player to the other
void Game::switch_player() {
    if(active_player == white) {
        active_player = black; 
    } else {
        active_player = white;
    }
}

//Main Game loop. 
void Game::Loop() {
    sf::Event event;
    while (graphics_->window_open()) {
        while (graphics_->poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                graphics_->close_window();
                break;
            } else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                ui_->interact(event);
            }
        }
        graphics_->clear();      //Clear previously drawn screen
        graphics_->draw();       //Draw, depending in current game state
        graphics_->display();    //Show the drawing
    }
}

