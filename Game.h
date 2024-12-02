#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Taxi.h"
#include <vector>

class Game {
public:
    Game(sf::RenderWindow& window);
    void run();
    void render(sf::RenderWindow& window);

private:
    sf::RenderWindow& window;
    std::vector<Taxi> taxies;
    std::vector<bool> isMoving;

    sf::Clock clock; 

    void updateTaxis(); 
    void createTaxi();
};

#endif
