#ifndef GAME_H
#define GAME_H

//#include "Graphics.cpp"
#include "Movement.cpp"
#include "Board.cpp"
#include "highlight.cpp"
#include "outline.cpp"
#include "window.hpp"

//Forward delc. of UI to prevent circle dependancy
class UI;
class Graphics;
class DataLoader;

class Game
{
    public:
        Game();
        ~Game();
        void Loop();
        Board* get_board() { return board_; }
        Movement* get_movement() { return movement_; }
        Highlight* get_highlighter() { return highlighter_; }
        Outline* get_outliner() { return outliner_; }
        COLOR get_active_player() { return active_player; }
        Window* get_window() { return window_; }
        void switch_player();

    private:
        bool was_piece_clicked(Pos pos_clicked);
        void piece_clicked(Pos pos);
        bool move_clicked(Pos pos_clicked);
        COLOR active_player;
        Board* board_;
        Graphics* graphics_;
        Movement* movement_;
        Highlight* highlighter_;
        Outline* outliner_;
        DataLoader* dataloader_;
        UI* ui_;
        Window* window_;
};

#endif
