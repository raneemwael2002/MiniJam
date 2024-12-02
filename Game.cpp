#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) : window(window) {
    createTaxi();
}

void Game::run() {
    if (clock.getElapsedTime().asSeconds() >= 2.f) {
        createTaxi();
        clock.restart();
    }

    updateTaxis(); 
}

void Game::render(sf::RenderWindow& window) {
    for (auto& taxi : taxies) {
        taxi.draw(window);
    }
}

void Game::updateTaxis() {
    const float spacing = 50.f;  
    const float lineHeight = 50.f;  
    const float verticalSpeed = 5.f;  
    
    for (size_t i = 0; i < taxies.size(); ++i) {
        sf::Vector2f position = isMoving[i] ? taxies[i].getPosition() : sf::Vector2f(taxies[i].getPosition().x, (int)(i / 15) * 20 + 20);

        if (position.y <= (int)(i/15)*20+20) {
            isMoving[i] = false;
            if (i > 0) {
                sf::Vector2f prevPosition = taxies[i - 1].getPosition();

               
                if (prevPosition.x - spacing < 0) {
                   
                    position.x = window.getSize().x - spacing*4;
                    position.y = prevPosition.y + lineHeight;
                }
                else {
                   
                    position.x = prevPosition.x - spacing ;
                    position.y = prevPosition.y;
                }
            }
            else {
                
                position.x = window.getSize().x - spacing * 4;
                position.y = (int)(i / 15) * 20 + 20;
            }
        }
        else {
            position.y -= verticalSpeed;
        }

        taxies[i].setPosition(position);
    }
}


void Game::createTaxi() {


    sf::Vector2f bottomRight(window.getSize().x - 120.f, window.getSize().y - 40.f);
    Taxi taxi(20.f, bottomRight, sf::Color::Yellow);
    taxies.push_back(taxi);
    isMoving.push_back(true);

    sf::Vector2f bottomLeft(window.getSize().x - 600.f, window.getSize().y - 40.f);
    Taxi leftTaxi(20.f, bottomLeft, sf::Color::Yellow);
    taxies.push_back(leftTaxi);
    isMoving.push_back(true);

}
