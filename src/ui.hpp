#ifndef UI_H
#define UI_H

#include "pos.hpp"
#include "game.hpp"
#include <SFML/Window.hpp>

class UI {
    Game* game_;
    bool was_piece_clicked(Pos pos_clicked);
    void piece_clicked(Pos pos);
    bool move_clicked(Pos pos_clicked);
public:
    UI(Game* game);
    ~UI() {}
    void interact(sf::Event);
};

#endif
