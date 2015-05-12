#include "game.hpp"

//Ctor
Game::Game() {
    board_ = new Board;
    graphics_ = new Graphics(board_);
    movement_ = new Movement(board_);
    board_->initialize_board();
    board_->set_highlight(5,4, true);
    board_->set_outline(4,4,true);
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
            } else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                Pos pos = board_->find_clicked_pos(event.mouseButton.x, event.mouseButton.y);
                if(board_->check_space(pos.x_, pos.y_) != NULL) {
                    board_->set_active_piece(board_->check_space(pos.x_, pos.y_));
                    board_->clear_all_outlines();
                    board_->set_outline(pos.x_, pos.y_, true);
                    std::cout << board_->get_active_piece();
                    movement_->highlight_valid_moves(movement_->get_valid_moves(board_->check_space(pos.x_, pos.y_)));
                }
            //Tests
            } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                board_->move_space(0,1, 3,3);
                board_->move_space(3,1, 5,3);
                board_->clear_all_highlights();
                board_->clear_all_outlines();
                //movement_->highlight_valid_moves(movement_->get_valid_moves(board_->check_space(0, 0)));
            }
        }
        graphics_->clear();      //Clear previously drawn screen
        graphics_->draw();  //Draw, depending in current game state
        graphics_->display();    //Show the drawing
    }
}

