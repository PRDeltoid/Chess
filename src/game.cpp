#include "game.hpp"

//Ctor
Game::Game() {
    board_ = new Board;
    highlighter_ = new Highlight(board_);
    outliner_ = new Outline(board_);
    graphics_ = new Graphics(board_, highlighter_, outliner_);
    movement_ = new Movement(board_);
    dataloader_ = new DataLoader(board_);
    board_->initialize_board();
    dataloader_->load_pieces("data");
    active_player = white;
}

Game::~Game() {
    delete graphics_;
    delete board_;
    delete movement_;
    delete highlighter_;
    delete outliner_;
    delete dataloader_;
}

void Game::switch_player() {
    if(active_player == white) {
        active_player = black; 
    } else {
        active_player = white;
    }
}

bool Game::was_piece_clicked(Pos pos_clicked) {
    //Determine if the position had a piece, and the piece clicked belongs to the current player
    if(!board_->check_empty(pos_clicked.x_, pos_clicked.y_) && 
        board_->check_space(pos_clicked.x_, pos_clicked.y_)->get_color() == active_player) {
        return true;
    } else {
        return false;
    }
}

void Game::piece_clicked(Pos pos) {
    Piece* clicked_piece = board_->check_space(pos.x_, pos.y_);
    board_->set_active_piece(clicked_piece);            //Set the clicked piece to active
    outliner_->clear_all_outlines();                       //Clear previous outlines
    outliner_->set_outline(pos.x_, pos.y_, true);          //Create an outline around the clicked piecce
    highlighter_->clear_all_highlights();
    vector<Pos> valid_moves = movement_->get_valid_moves(clicked_piece);
    highlighter_->highlight_valid_moves(valid_moves);    //Highlight the valid moves for the piece
}

//Main Game loop. 
void Game::Loop() {
    sf::Event event;
    while (graphics_->window_open()) {
        while (graphics_->poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                graphics_->close_window();
            } else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                //Get the position that was clicked
                Pos pos_clicked = board_->find_clicked_pos(event.mouseButton.x, event.mouseButton.y);
                //Determine if the position had a piece, and the piece clicked belongs to the current player
                if(was_piece_clicked(pos_clicked))
                    piece_clicked(pos_clicked);
            }
        }
        graphics_->clear();      //Clear previously drawn screen
        graphics_->draw();       //Draw, depending in current game state
        graphics_->display();    //Show the drawing
    }
}

