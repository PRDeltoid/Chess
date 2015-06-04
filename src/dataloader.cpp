#include "dataloader.hpp"

DataLoader::DataLoader(Board* board, Graphics* graphics) {
    board_ = board;
    graphics_ = graphics;
}

void DataLoader::load_pieces(std::string filename) {
    //Open the data file
    std::ifstream datafile;
    datafile.open(filename.c_str());
    //Read data file if open
    if(datafile.is_open()) {
        Piece* piece;
        int piece_x,
            piece_y;
        std::string piece_color,
                    piece_type;
        while(datafile >> piece_x) {
            datafile >> piece_y;
            datafile >> piece_color;
            datafile >> piece_type;
            //Create the piece after reading
            piece = new Piece(piece_type, piece_color);  
            //std::cout << graphics_->find_piece_graphic(piece->get_type(), piece->get_color());
            piece->set_shape(graphics_->find_piece_graphic(piece->get_type(), piece->get_color()));
            board_->add_piece(piece);
            //Set up the piece on the board
            board_->set_space(piece_x, piece_y, piece);
        }
    }
}
