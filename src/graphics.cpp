#include "graphics.hpp"

//Ctor
Graphics::Graphics(Game* game) {
    window_ = game->get_window();
    board_  = game->get_board();
    highlighter_ = game->get_highlighter();
    outliner_ = game->get_outliner();
    initialize();
}

Graphics::~Graphics() {
    delete white_king_;
    delete white_queen_;
    delete white_bishop_;
    delete white_knight_;
    delete white_rook_;
    delete white_pawn_;
    delete black_king_;
    delete black_queen_;
    delete black_bishop_;
    delete black_knight_;
    delete black_rook_;
    delete black_pawn_;
}

//Load piece graphics. 
//Create the board pieces (not the chess pieces, the board squares)
//Clip the chess piece sprites from the spritesheet
//Setup highlight graphic
//Setup Outline graphic
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

//Loop through the board and draw all the squares.
//If a square has a piece, render the piece. 
//If a square has highlight/outline, render that.
void Graphics::draw() {
    for(int i=0;i<BOARDSIZE;i++) {
        int x = i%SIDESIZE; //Get the x coordinate for the space to draw
        int y = i/SIDESIZE; //Get the y coordinate for the space to draw
        window_->draw(board_shapes_[i]); //Draw the board background

        if(board_->check_space(x, y) != 0) {
            Piece* piece = board_->check_space(x, y);
            sf::RectangleShape* piece_shape = piece->get_shape();
            piece_shape->setPosition((x)*SQUARESIZE, (y)*SQUARESIZE);
            window_->draw(*piece_shape);
        }

        //If highlight is true, highlight the square
        if(highlighter_->check_hightlight(x, y) == true)
            highlight_square(x, y);
        if(outliner_->check_outline(x, y) == true)
            outline_square(x, y);
    }
}

//Interface to clear the window.
void Graphics::clear() {
    window_->clear();
}

//Interface to display the window's shapes
void Graphics::display() {
    window_->display();
}

//Encasulating function for clear/draw/display
void Graphics::render() {
    clear();
    draw();
    display();
}

//Clip a single chess piece graphics and store it in the piece variable
sf::RectangleShape* Graphics::clip_piece(int from_left, int from_top) {
    //Create a clipping rectangle size 100x100 pixels. Position it using from_left and from_top
    sf::Rect<int> clip_rect;
    clip_rect.height = clip_rect.width = SQUARESIZE;
    clip_rect.top = from_top * SQUARESIZE;
    clip_rect.left = from_left * SQUARESIZE;

    //Use the clipping rect to clip a square from the spritesheet and store it in the piece.
    sf::RectangleShape* piece = new sf::RectangleShape(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    piece->setTexture(&texture_sheet_, false);
    piece->setTextureRect(clip_rect);
    return piece;
}

//Go through the spritesheet and clip the chess piece graphics
void Graphics::clip_all_pieces() {
    white_king_ = clip_piece(0, 0);
    black_king_ = clip_piece(0, 1);

    white_queen_ = clip_piece(1, 0);
    black_queen_ = clip_piece(1, 1);

    white_bishop_ = clip_piece(2, 0);
    black_bishop_ = clip_piece(2, 1);

    white_knight_ = clip_piece(3, 0);
    black_knight_ = clip_piece(3, 1);
    
    white_rook_ = clip_piece(4, 0);
    black_rook_ = clip_piece(4, 1);
    
    white_pawn_ = clip_piece(5, 0);
    black_pawn_ = clip_piece(5, 1);
}

//Loads a spritesheet from a file
void Graphics::load_spritesheet(std::string filename) {
    texture_image_.loadFromFile(filename); 
    texture_image_.createMaskFromColor(sf::Color::Green, 0); //Transparency key
    texture_sheet_.loadFromImage(texture_image_);
    texture_sheet_.setSmooth(true); //Smooth edges
}

//Returns the piece graphic to use depending on piece type and color
sf::RectangleShape* Graphics::find_piece_graphic(TYPE piece_type, COLOR piece_color) {
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

//Draw a highlight over position x and y
void Graphics::highlight_square(int x, int y) {
    //Move the highlight into position
    highlight_.setPosition((x)*SQUARESIZE, (y)*SQUARESIZE);
    //Draw the highlighted square
    window_->draw(highlight_);
}

//Draw a outline over position x and y
void Graphics::outline_square(int x, int y) {
    outline_.setPosition((x)*SQUARESIZE+OUTLINEWIDTH, (y)*SQUARESIZE+OUTLINEWIDTH);
    window_->draw(outline_);
}
