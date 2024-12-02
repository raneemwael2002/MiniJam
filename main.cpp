#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Taxi Game");
    window.setFramerateLimit(60);

    Game game(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game.run(); 
        window.clear();
        game.render(window); 
        window.display();
    }

    return 0;
}
