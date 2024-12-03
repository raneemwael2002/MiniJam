#include "Taxi.h"

Taxi::Taxi(const TaxiTexture& texture, const sf::Vector2f& initialPosition, const sf::Vector2f& size) {
    sprite.setTexture(texture.getTexture());
    float scaleX = size.x / texture.getTexture().getSize().x;
    float scaleY = size.y / texture.getTexture().getSize().y;
    sprite.setScale(scaleX, scaleY);
    sprite.setOrigin(texture.getTexture().getSize().x / 2.f, texture.getTexture().getSize().y / 2.f);
    sprite.setPosition(initialPosition);
}

void Taxi::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Taxi::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

sf::Vector2f Taxi::getPosition() const {
    return sprite.getPosition();
}
