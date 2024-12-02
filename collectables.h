#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Collectables {
public:
    Collectables(b2World& world, float radius, const sf::Vector2f& initialPosition, const sf::Color& color);
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape shape;   // SFML visual representation
    b2Body* body;            // Box2D body for physics simulation
};
