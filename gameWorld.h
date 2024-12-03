#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "player.h"
#include "Taxi.h"
#include "CollisionListener.h"
#include "Projectile.h"
class gameWorld {
private:
    b2World& world;
    std::vector<bool> isMoving;
    float windowWidth;
    float windowHeight;
    Player* player;
    Taxi* taxi;
    Projectile* projectile;
    CollisionListener* collisionListener;
public:
    std::vector<Taxi> taxies;
    gameWorld(b2World& world, sf::RenderWindow& window);
    void createPlayer();
    void createTaxi(sf::RenderWindow& window);
    void run(sf::RenderWindow& window);
    void handleInput();
    void gameUpdate(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, float deltaTime);
    void updateTaxis(sf::RenderWindow& window);
};
