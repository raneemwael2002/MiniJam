#pragma once
#include <SFML/Graphics.hpp>

class TaxiTexture {
public:
    TaxiTexture();
    const sf::Texture& getTexture() const;
    bool isLoaded() const;

private:
    sf::Texture texture;
    bool loaded;
};