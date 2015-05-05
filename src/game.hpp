#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <sstream>
#include "Graphics.cpp"

class Game
{
    public:
        Game();
        void Loop();
    private:
        Board* board;
        Graphics* graphics;
};


#endif
