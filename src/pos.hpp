#ifndef POS_H
#define POS_H

struct Pos {
    public:
        Pos(int x, int y) :
            x_(x),
            y_(y)
        {}
        Pos() {}
        void set_pos(int x, int y) { x_=x; y_=y; }
        int x_,
            y_;
};

#endif
