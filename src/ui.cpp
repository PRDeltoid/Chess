#include "ui.hpp"

UI::UI(Game* game) {
    game_ = game;
    outliner_ = game_->get_outliner();
    highlighter_ = game_->get_highlighter();
    movement_ = game_->get_movement();
    board_ = game_->get_board();
}

//WILL BE CHANGED
//Currently takes a click event and handles it
//Will eventually take other events
void UI::interact(sf::Event event) {
    //Get the position that was clicked
    Pos pos_clicked = game_->get_board()->find_clicked_pos(event.mouseButton.x, event.mouseButton.y);
    //Determine if the position clicked is a valid move (only if there is an active piece)
    //If it is, move the piece
    if(game_->get_board()->get_active_piece() != NULL && move_clicked(pos_clicked)) {
        return;
    }
    //Determine if the position had a piece, and the piece clicked belongs to the current player
    if(was_piece_clicked(pos_clicked))
        piece_clicked(pos_clicked);
}
 
//Check if the position clicked has a piece on it
//and that the piece is OWNED by the active player
bool UI::was_piece_clicked(Pos pos_clicked) {
    Board* board = game_->get_board();
    if(!board->check_empty(pos_clicked.x_, pos_clicked.y_) && 
        board->check_space(pos_clicked.x_, pos_clicked.y_)->get_color() == game_->get_active_player()) {
        return true;
    } else {
        return false;
    }
    return true;
}

//Function to determine what to do when a piece is clicked
//The Pos passed is the location that was clicked (which is already known
//to have a piece on it)
void UI::piece_clicked(Pos pos) {
    Piece* clicked_piece = board_->check_space(pos.x_, pos.y_);

    if(board_->get_active_piece() == clicked_piece)        //Check if the piece clicked is already active
        return;                                           
    board_->set_active_piece(clicked_piece);               //Set the clicked piece to active
    outliner_->clear_all_outlines();                       //Clear previous outlines
    outliner_->set_outline(pos.x_, pos.y_, true);          //Create an outline around the clicked piecce
    highlighter_->clear_all_highlights();                  //Clear all previous highlighting
    vector<Pos> valid_moves = movement_->get_valid_moves(clicked_piece); //Get the valid moves for the piece
    highlighter_->highlight_valid_moves(valid_moves);      //Highlight the valid moves for the piece
}

//Checks if the clicked pos is a valid move
//If it is, move the piece and return true
//Otherwise, return false (ie. the move was not a valid one)
bool UI::move_clicked(Pos pos_clicked) {
    //Valid move is true if the move was valid,
    bool valid_move = movement_->is_valid_move(pos_clicked);
    //If the move clicked was valid, move the piece, clear all the effects and switch players
    if(valid_move) {  
        Pos piece_pos = game_->get_board()->find_piece_pos(game_->get_board()->get_active_piece());
        //Move the piece
        movement_->move_piece(piece_pos, pos_clicked);
        //clear the board of all highlighting/outlining etc.
        highlighter_->clear_all_highlights();
        outliner_->clear_all_outlines();
        movement_->clear_valid_moves();
        //Lastly, switch the active player
        game_->switch_player();
    }
    return valid_move;
}
