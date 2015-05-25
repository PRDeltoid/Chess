#include "ui.hpp"

UI::UI(Game* game) {
    game_ = game;
}

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

void UI::piece_clicked(Pos pos) {
    Board* board = game_->get_board();
    Outline* outliner = game_->get_outliner();
    Highlight* highlighter = game_->get_highlighter();
    Movement* movement = game_->get_movement();
    Piece* clicked_piece = board->check_space(pos.x_, pos.y_);

    if(board->get_active_piece() == clicked_piece)        //Check if the piece clicked is already active
        return;                                           
    board->set_active_piece(clicked_piece);               //Set the clicked piece to active
    outliner->clear_all_outlines();                       //Clear previous outlines
    outliner->set_outline(pos.x_, pos.y_, true);          //Create an outline around the clicked piecce
    highlighter->clear_all_highlights();                  //Clear all previous highlighting
    vector<Pos> valid_moves = movement->get_valid_moves(clicked_piece); //Get the valid moves for the piece
    highlighter->highlight_valid_moves(valid_moves);      //Highlight the valid moves for the piece
}

bool UI::move_clicked(Pos pos_clicked) {
    Outline* outliner = game_->get_outliner();
    Highlight* highlighter = game_->get_highlighter();
    Movement* movement = game_->get_movement();
    bool valid_move = movement->is_valid_move(pos_clicked);
    if(valid_move) {  
        //clear the board of all highlighting/outlining etc.
        highlighter->clear_all_highlights();
        outliner->clear_all_outlines();
        movement->clear_valid_moves();
        //Lastly, switch the active player
        game_->switch_player();
    }
    return valid_move;

    return true;
}
