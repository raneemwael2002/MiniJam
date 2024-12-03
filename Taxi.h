#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Taxi {
public:
    Taxi(b2World& world, float radius, sf::Vector2f position, sf::Color color);

    sf::Vector2f getPosition() const;
    float getRadius() const;
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);

private:
    b2World& world;
    b2Body* body;
    sf::CircleShape shape;        // Optional, for debugging with circle
    sf::Sprite sprite;            // Sprite for the taxi image
    sf::Texture taxiTexture;      // Texture for the taxi image
};