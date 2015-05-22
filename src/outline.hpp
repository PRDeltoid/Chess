#ifndef OUTLINE_H
#define OUTLINE_H

#include <vector>
#include <iostream>
#include "pos.hpp"
#include "board.hpp"

using std::vector;

class Outline {
    public:
        Outline(Board* board);
        ~Outline() {}
        bool check_outline(int x, int y);
        void set_outline(int x, int y, bool truefalse);
        void clear_all_outlines();
    private:
        Board* board_;
        Space* spaces_;
};

#endif
