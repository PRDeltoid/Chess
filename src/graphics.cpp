#include "graphics.hpp"

Graphics::Graphics(Game* game) {
    window_ = game->get_window();
    board_  = game->get_board();
    highlighter_ = game->get_highlighter();
    outliner_ = game->get_outliner();
    initialize();
}

void Graphics::initialize() {
    load_spritesheet("assets/sprites/Chess_Pieces_Sprite.bmp"); //Load spritesheet
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

    //make the highlight square
    sf::Color highlight_color(255, 255, 0, 150);
    highlight_.setFillColor(highlight_color);
    highlight_.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    
    //make the outline square
    sf::Color outline_color(255, 0, 0);
    outline_.setFillColor(sf::Color::Transparent);
    outline_.setOutlineThickness(static_cast<float>(OUTLINEWIDTH));
    outline_.setOutlineColor(outline_color);
    outline_.setSize(sf::Vector2f(SQUARESIZE-(OUTLINEWIDTH*2), SQUARESIZE-(OUTLINEWIDTH*2)));
}

void Graphics::draw() {
    for(int i=0;i<BOARDSIZE;i++) {
        int x = i%SIDESIZE; //Get the x coordinate for the space to draw
        int y = i/SIDESIZE; //Get the y coordinate for the space to draw
        window_->draw(board_shapes_[i]); //Draw the board background
        //If a piece is found, draw the piece.
        if(board_->check_space(x, y) != NULL)
            render_piece(x, y); 
        //If highlight is true, highlight the square
        if(highlighter_->check_hightlight(x, y) == true)
            highlight_square(x, y);
        if(outliner_->check_outline(x, y) == true)
            outline_square(x, y);
    }
}

void Graphics::clear() {
    window_->clear();
}

void Graphics::display() {
    window_->display();
}

void Graphics::render() {
    clear();
    draw();
    display();
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

void Graphics::render_piece(int x, int y) {
    //Find the type and color of the piece in question
    TYPE type = board_->check_space(x, y)->get_type();
    COLOR color = board_->check_space(x, y)->get_color();
    //Find the corrisponding graphic for piece of above type and color
    sf::RectangleShape piece = find_piece_graphic(type, color);
    //Move the graphic to the position of the piece on the board
    piece.setPosition((x)*SQUARESIZE, (y)*SQUARESIZE);
    //Draw the piece
    window_->draw(piece);
}

void Graphics::highlight_square(int x, int y) {
    //Move the highlight into position
    highlight_.setPosition((x)*SQUARESIZE, (y)*SQUARESIZE);
    //Draw the highlighted square
    window_->draw(highlight_);
}

void Graphics::outline_square(int x, int y) {
    outline_.setPosition((x)*SQUARESIZE+OUTLINEWIDTH, (y)*SQUARESIZE+OUTLINEWIDTH);
    window_->draw(outline_);
}
