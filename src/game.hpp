#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Graphics.cpp"
#include "Movement.cpp"
#include "Board.cpp"

class Game
{
    public:
        Game();
        ~Game();
        void Loop();
    private:
        Board* board_;
        Graphics* graphics_;
        Movement* movement_;
};

#endif
