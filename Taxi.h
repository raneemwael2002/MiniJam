#pragma once
#include <SFML/Graphics.hpp>
#include "TaxiTexture.h"

class Taxi {
public:
    Taxi(const TaxiTexture& texture, const sf::Vector2f& initialPosition, const sf::Vector2f& size);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
};
