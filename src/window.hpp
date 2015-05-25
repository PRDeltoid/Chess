#ifndef WINDOW_H
#define WINDOW_H

#include <SFML\Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 800;

class Window {
    sf::RenderWindow* window_;
public:
    Window() { window_ = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Chess", sf::Style::Close); }
    sf::RenderWindow* get_window() { return window_; }
    bool is_open() { return window_->isOpen(); }
    void display() { window_->display(); }
    void close() { window_->close(); }
    void clear() { window_->clear(); }
    void draw(sf::RectangleShape rect) { window_->draw(rect); }
    bool poll_event(sf::Event& event) { return window_->pollEvent(event); }
};

#endif
