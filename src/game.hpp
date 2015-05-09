#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Graphics.cpp"

class Game
{
    public:
        Game();
        ~Game();
        void Loop();
    private:
        Board* board;
        Graphics* graphics;
};

#endif
