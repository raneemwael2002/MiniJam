#include "projectile.h"
#include <cmath>
#include <iostream>
Projectile::Projectile(b2World& world, float x, float y, float speed, float angle, float radius, float scaleFactor)
    : scale(scaleFactor) {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / scale, y / scale);
    body = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = radius / scale;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    // Set the user data for the projectile
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    // Set up the sprite
    if (!texture.loadFromFile("assets/Shoot.png")) {
        std::cerr << "Error loading projectile texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);  // Set origin to center
    sprite.setScale(0.05f, 0.1f);
    sprite.setPosition(x, y);

    float velocityX = speed * std::cos(angle);
    float velocityY = speed * std::sin(angle);
    body->SetLinearVelocity(b2Vec2(velocityX / scale, velocityY / scale));


}
 

void Projectile::update() {
    b2Vec2 position = body->GetPosition();
    sprite.setPosition(position.x * scale, position.y * scale);
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

b2Vec2 Projectile::getPosition() const {
    return body->GetPosition();
}
