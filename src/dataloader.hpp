#ifndef DATALOADER_H
#define DATALOADER_H

#include "board.hpp"
#include <fstream>

class DataLoader {
    public:
        DataLoader(Board* board);
        ~DataLoader() {}
        void load_pieces(std::string filename);
    private:
        Board* board_;
};

#endif
