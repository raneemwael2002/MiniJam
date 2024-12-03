#include "gameWorld.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>



gameWorld::gameWorld(b2World& world, sf::RenderWindow& window)
    : world(world), player(nullptr), windowWidth(window.getSize().x), windowHeight(window.getSize().y) {
    createPlayer();
    collisionListener = new CollisionListener(*player, *taxi, *projectile);
    world.SetContactListener(collisionListener);
}

void gameWorld::createPlayer() {
    player = new Player(world, 400.f, 500.f, 20.f, 30.f);
}

void gameWorld::createTaxi(sf::RenderWindow& window) {
    // Create taxis on both sides
    sf::Vector2f bottomLeft(window.getSize().x - 900.0f, window.getSize().y - 80.f);
    sf::Vector2f bottomRight(window.getSize().x - 280.0f, window.getSize().y - 80.f);
    Taxi taxi1(world,20.f, bottomLeft, sf::Color::Yellow);
    Taxi taxi2(world, 20.f, bottomRight, sf::Color::Yellow);

  
    taxies.push_back(taxi1);
    isMoving.push_back(true);
    taxies.push_back(taxi2);
    isMoving.push_back(true);

}

void gameWorld::handleInput() {
    player->handleInput(world);
}

void gameWorld::gameUpdate(sf::RenderWindow& window) {
    player->update();
    run(window);
}

void gameWorld::updateTaxis(sf::RenderWindow& window) {
    const float spacing = 50.f;
    const float lineHeight = 50.f;
    const float verticalSpeed = 10.f;
    const float leftMargin = 3.f;

    for (size_t i = 0; i < taxies.size(); ++i) {
        sf::Vector2f position = isMoving[i] ? taxies[i].getPosition()
            : sf::Vector2f(taxies[i].getPosition().x, (int)(i / 10) * 10 + 20);

        if (position.y <= (int)(i / 10) * 10 + 20) {
            isMoving[i] = false;
            if (i > 0) {
                sf::Vector2f prevPosition = taxies[i - 1].getPosition();

                if (prevPosition.x - spacing < leftMargin) {
                    position.x = window.getSize().x - spacing * 7;
                    position.y = prevPosition.y + lineHeight;
                }
                else {
                    position.x = prevPosition.x - spacing;
                    position.y = prevPosition.y;
                }
            }
            else {
                position.x = window.getSize().x - spacing * 7;
                position.y = (int)(i / 10) * 10 + 20;
            }
        }
        else {
            position.y -= verticalSpeed;
        }

        taxies[i].setPosition(position);
    }
}

void gameWorld::draw(sf::RenderWindow& window, float deltaTime) {
    renderer::drawBackGround(window, deltaTime);
    renderer::drawPlayer(window, player);
    renderer::drawTaxi(window, taxies);
    window.display();
}

void gameWorld::run(sf::RenderWindow& window) {
    static sf::Clock clock;
    const float taxiSpawnInterval = 2.0f;
    if (clock.getElapsedTime().asSeconds() >= taxiSpawnInterval) {
       
        createTaxi(window);
        clock.restart();
  
    }
        
        updateTaxis(window);
        
}