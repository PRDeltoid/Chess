#ifndef SPACE_H
#define SPACE_H

#include "piece.hpp"

struct Space {
    Piece* piece_;
    bool highlight_;
    bool outline_;
};

#endif
