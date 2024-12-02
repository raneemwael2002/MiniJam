#ifndef TAXI_H
#define TAXI_H

#include <SFML/Graphics.hpp>

class Taxi {
public:
    Taxi(float radius, const sf::Vector2f& initialPosition, const sf::Color& color);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape Shape;
};

#endif
