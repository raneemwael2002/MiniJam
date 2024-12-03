#include <SFML/Graphics.hpp>
#include "Game.h"
#include "TaxiTexture.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Taxi Game");
    window.setFramerateLimit(60);
    TaxiTexture taxiTexture;
       if (!taxiTexture.isLoaded()) {
        return -1;
    }
    Game game(window, taxiTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            /*game.handleClick(event);*/
        }
        
        game.run(); 
        game.update();
        window.clear();
        game.render(window); 
        window.display();
    }

    return 0;
}
