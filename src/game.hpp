#ifndef GAME_H
#define GAME_H

#include "Graphics.cpp"
#include "Movement.cpp"
#include "Board.cpp"
#include "highlight.cpp"
#include "outline.cpp"
#include "dataloader.cpp"

class Game
{
    public:
        Game();
        ~Game();
        void Loop();
    private:
        void switch_player();
        bool was_piece_clicked(Pos pos_clicked);
        void piece_clicked(Pos pos); //TODO
        COLOR active_player;
        Board* board_;
        Graphics* graphics_;
        Movement* movement_;
        Highlight* highlighter_;
        Outline* outliner_;
        DataLoader* dataloader_;
};

#endif
