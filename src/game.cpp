#include "game.hpp"
#include "ui.cpp"
#include "graphics.cpp"
#include "dataloader.cpp"

//Ctor
Game::Game() {
    board_       = new Board;
    highlighter_ = new Highlight(board_);
    outliner_    = new Outline(board_);
    window_      = new Window();
    movement_    = new Movement(board_);
    graphics_    = new Graphics(this);
    dataloader_  = new DataLoader(board_, graphics_);
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
    delete ui_;
    delete window_;
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
    while (window_->is_open()) {
        while (window_->poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                window_->close();
                break;
            } else if(event.type == sf::Event::MouseButtonPressed &&
                      event.mouseButton.button == sf::Mouse::Left) {
                ui_->interact(event);
            }
        }
        graphics_->render();
    }
}

