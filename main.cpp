//#include <SFML\Graphics.hpp>
#include <iostream>
#include "src\game.cpp"
#include "src\board.cpp"
#include "src\graphics.cpp"

int main()
{
    /*Graphics graphics;
    graphics.initialize();
    Board board;
    board.initialize_board();*/
    Game game;
    game.Loop();
    return 0;
}
