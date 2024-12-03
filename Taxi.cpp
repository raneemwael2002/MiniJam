#include "Taxi.h"
#include <iostream>

Taxi::Taxi(b2World& world, float radius, sf::Vector2f position, sf::Color color)
    : world(world), shape(radius) {
    // Load the texture
    if (!taxiTexture.loadFromFile("assets/Taxi0.png")) {
        std::cerr << "Error loading taxi texture!" << std::endl;
    }

    // Setup sprite
    sprite.setTexture(taxiTexture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);
    sprite.setScale(0.05f, 0.1f);  // Scaling the sprite for a better fit

    // Create physics body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    body = world.CreateBody(&bodyDef);

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    // Create a circle shape for physics
    b2CircleShape circleShape;
    circleShape.m_radius = radius;

    // Define the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;  // Mass
    fixtureDef.friction = 0.3f;  // Friction
    body->CreateFixture(&fixtureDef);
}

sf::Vector2f Taxi::getPosition() const {
    return sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

float Taxi::getRadius() const {
    return shape.getRadius();
}

void Taxi::setPosition(const sf::Vector2f& position) {
    body->SetTransform(b2Vec2(position.x, position.y), body->GetAngle());
}

void Taxi::draw(sf::RenderWindow& window) {
    // Update the sprite's position based on the physics body position
    sprite.setPosition(getPosition());
    window.draw(sprite);  // Draw the sprite with the texture
}
