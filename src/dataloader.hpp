#ifndef DATALOADER_H
#define DATALOADER_H

#include "board.hpp"
#include "graphics.hpp"
#include <fstream>

class DataLoader {
    public:
        DataLoader(Board* board, Graphics* graphics);
        ~DataLoader() {}
        void load_pieces(std::string filename);
    private:
        Board* board_;
        Graphics* graphics_;
};

#endif
