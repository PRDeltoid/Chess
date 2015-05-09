#include "graphics.hpp"

Graphics::Graphics() {
    window_.create(sf::VideoMode(WIDTH, HEIGHT), "Chess", sf::Style::Close); //Create an unresizable window
    load_spritesheet("Chess_Pieces_Sprite.bmp"); //Load spritesheet

    //Create the board's shapes (not the pieces).
    sf::Color black(136, 0, 12); //Alternative black.
    for(int i=0;i<BOARDSIZE;i++) {
        if((i%2==0 && (i/8)%2==0) || (i%2==1 && (i/8)%2==1)) {
            board_shapes_[i].setFillColor(sf::Color::White);
        } else {
            board_shapes_[i].setFillColor(black);
        }
        board_shapes_[i].setPosition((i%SIDESIZE)*SQUARESIZE, (i/SIDESIZE)*SQUARESIZE);
        board_shapes_[i].setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    }

    //Clip the piece sprites. 
    clip_all_pieces();
}

bool Graphics::window_open() {
    return window_.isOpen();
}

void Graphics::display() {
    window_.display();
}

void Graphics::draw(Board* board) {
    for(int i=0;i<BOARDSIZE;i++) {
        window_.draw(board_shapes_[i]);
        //If a piece is found, draw the piece.
        if(board->check_space(i%SIDESIZE, i/SIDESIZE) != NULL) {
            //Find the type and color of the piece in question
            TYPE type = board->check_space(i%SIDESIZE, i/SIDESIZE)->get_type();
            COLOR color = board->check_space(i%SIDESIZE, i/SIDESIZE)->get_color();
            //Find the corrisponding graphic for piece of above type and color
            sf::RectangleShape piece = find_piece_graphic(type, color);
            //Move the graphic to the position of the piece on the board
            piece.setPosition((i%SIDESIZE)*SQUARESIZE, (i/SIDESIZE)*SQUARESIZE);
            //Draw the piece
            window_.draw(piece);
        }
    }
}

void Graphics::clear() {
    window_.clear();
}

void Graphics::close_window() {
    window_.close();
}

bool Graphics::poll_event(sf::Event& event) {
    return window_.pollEvent(event);
}

void Graphics::clip_piece(sf::RectangleShape& piece, int from_left, int from_top) {
    //Create a clipping rectangle size 100x100 pixels. Position it using from_left and from_top
    sf::Rect<int> clip_rect;
    clip_rect.height = clip_rect.width = SQUARESIZE;
    clip_rect.top = from_top * SQUARESIZE;
    clip_rect.left = from_left * SQUARESIZE;

    //Use the clipping rect to clip a square from the spritesheet and store it in the piece.
    piece.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    piece.setTexture(&texture_sheet_, false);
    piece.setTextureRect(clip_rect);
}

void Graphics::clip_all_pieces() {
    clip_piece(white_king_, 0, 0);
    clip_piece(black_king_, 0, 1);

    clip_piece(white_queen_, 1, 0);
    clip_piece(black_queen_, 1, 1);

    clip_piece(white_bishop_, 2, 0);
    clip_piece(black_bishop_, 2, 1);

    clip_piece(white_knight_, 3, 0);
    clip_piece(black_knight_, 3, 1);
    
    clip_piece(white_rook_, 4, 0);
    clip_piece(black_rook_, 4, 1);
    
    clip_piece(white_pawn_, 5, 0);
    clip_piece(black_pawn_, 5, 1);
}

void Graphics::load_spritesheet(std::string filename) {
    texture_image_.loadFromFile(filename); 
    texture_image_.createMaskFromColor(sf::Color::Green, 0); //Transparency key
    texture_sheet_.loadFromImage(texture_image_);
    texture_sheet_.setSmooth(true); //Smooth edges
}

sf::RectangleShape Graphics::find_piece_graphic(TYPE piece_type, COLOR piece_color) {
    switch(piece_type) {
        case pawn:
            if(piece_color == white) return white_pawn_;
            else                     return black_pawn_;
            break;
        case rook:
            if(piece_color == white) return white_rook_;
            else                     return black_rook_;
            break;

        case knight:
            if(piece_color == white) return white_knight_;
            else                     return black_knight_;
            break;

        case bishop:
            if(piece_color == white) return white_bishop_;
            else                     return black_bishop_;
            break;

        case queen:
            if(piece_color == white) return white_queen_;
            else                     return black_queen_;
            break;

        case king:
            if(piece_color == white) return white_king_;
            else                     return black_king_;
            break;

        default:
            return white_pawn_;
            break;
    }
}
