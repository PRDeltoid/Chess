#include "graphics.hpp"

void Graphics::initialize() {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Chess");
}

bool Graphics::window_open() {
    return window.isOpen();
}

void Graphics::show() {
    window.display();
}

void Graphics::draw() {

}

void Graphics::clear() {
    window.clear();

}

void Graphics::close_window() {
    window.close();
}

bool Graphics::poll_event(sf::Event event) {
    return window.pollEvent(event);
}
