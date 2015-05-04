#include "game.hpp"

//Ctor
Game::Game() {
    graphics = new Graphics;
}

//Main Game loop. 
void Game::Loop() {
    while (graphics->window_open())
    {
        sf::Event event;
        while (graphics->poll_event(event))
        {
            if (event.type == sf::Event::Closed)
                graphics->close_window();
        }
        graphics->clear();   //Clear previously drawn screen
        graphics->draw();   //Draw, depending in current game state
        graphics->show();   //Show the drawing
    }
}

//Render the screen (drawing is done before this)
