#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
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
        Graphics* graphics;
};


#endif
