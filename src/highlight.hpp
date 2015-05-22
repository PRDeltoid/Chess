#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <vector>
#include <iostream>
#include "pos.hpp"
#include "board.hpp"

using std::vector;

class Highlight {
    public:
        Highlight(Board* board);
        ~Highlight() {}
        bool check_hightlight(int x, int y);
        void set_highlight(int x, int y, bool truefalse);
        void highlight_valid_moves(vector<Pos> valid_moves);
        void clear_all_highlights();
    private:
        Board* board_;
        Space* spaces_;
};

#endif
