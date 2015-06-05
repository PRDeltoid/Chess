#include "gfxPiece.hpp"

gfxPiece::gfxPiece(int SQUARESIZE) {
    SQUARESIZE_ = SQUARESIZE;
    load_spritesheet("assets/sprites/Chess_Pieces_Sprite.bmp"); //Load spritesheet
    clip_all_pieces();
}

gfxPiece::~gfxPiece() {
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


//Loads a spritesheet from a file
void gfxPiece::load_spritesheet(std::string filename) {
    texture_image_.loadFromFile(filename); 
    texture_image_.createMaskFromColor(sf::Color::Green, 0); //Transparency key
    texture_sheet_.loadFromImage(texture_image_);
    texture_sheet_.setSmooth(true); //Smooth edges
}


//Returns the piece graphic to use depending on piece type and color
sf::RectangleShape* gfxPiece::find_piece_graphic(TYPE piece_type, COLOR piece_color) {
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

//Clip a single chess piece graphics and store it in the piece variable
sf::RectangleShape* gfxPiece::clip_piece(int from_left, int from_top) {
    //Create a clipping rectangle size 100x100 pixels. Position it using from_left and from_top
    sf::Rect<int> clip_rect;
    clip_rect.height = clip_rect.width = SQUARESIZE_;
    clip_rect.top = from_top * SQUARESIZE_;
    clip_rect.left = from_left * SQUARESIZE_;

    //Use the clipping rect to clip a square from the spritesheet and store it in the piece.
    sf::RectangleShape* piece = new sf::RectangleShape(sf::Vector2f(SQUARESIZE_, SQUARESIZE_));
    piece->setTexture(&texture_sheet_, false);
    piece->setTextureRect(clip_rect);
    return piece;
}

//Go through the spritesheet and clip the chess piece graphics
void gfxPiece::clip_all_pieces() {
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
