#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML\Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;

class Graphics {
    public:
        Graphics() {}
        ~Graphics() {}
        void initialize();
        bool window_open();
        void draw();
        void clear();
        void show();
        void close_window();
        bool poll_event(sf::Event event);

    private:
        sf::RenderWindow window;
};

#endif
