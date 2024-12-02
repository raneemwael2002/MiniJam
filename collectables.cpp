#include "Collectables.h"

Collectables::Collectables(b2World& world, float radius, const sf::Vector2f& initialPosition, const sf::Color& color) {
    // Initialize SFML shape
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(initialPosition);

    // Define Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(initialPosition.x / 30.f, initialPosition.y / 30.f);
    body = world.CreateBody(&bodyDef);

    // Define Box2D shape and fixture
    b2CircleShape circleShape;
    circleShape.m_radius = radius / 30.f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

void Collectables::update() {
    // Synchronize SFML shape position with Box2D body
    b2Vec2 position = body->GetPosition();
    shape.setPosition(position.x * 30.f, position.y * 30.f);
}

void Collectables::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
