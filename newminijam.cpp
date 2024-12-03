#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "gameWorld.h"
#include "Player.h"
#include "Taxi.h"
#include"Projectile.h"
#include "CollisionListener.h"
int main() {
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);
    
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "TOKTOK Game");

    
    gameWorld game(world, window);
    game.createPlayer();
    
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game.handleInput();
        world.Step(1.0f / 60.0f, 8, 3); 
        float deltaTime = clock.restart().asSeconds();
        game.gameUpdate(window);
        game.draw(window, deltaTime); 
        window.clear();
    }

    return 0;
}
