#include "Taxi.h"

Taxi::Taxi(float radius, const sf::Vector2f& initialPosition, const sf::Color& color) {
    Shape.setRadius(radius);
    Shape.setFillColor(color);
    Shape.setOrigin(radius, radius);
    Shape.setPosition(initialPosition);
}

void Taxi::draw(sf::RenderWindow& window) {
    window.draw(Shape);
}

void Taxi::setPosition(const sf::Vector2f& position) {
    Shape.setPosition(position);
}

sf::Vector2f Taxi::getPosition() const {
    return Shape.getPosition();
}
