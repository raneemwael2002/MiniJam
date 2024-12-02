#pragma once
#include "projectile.h"
#include <cmath>

// Constructor for the Projectile class
Projectile::Projectile(b2World& world, float x, float y, float speed, float angle, float radius, float scaleFactor)
    : scale(scaleFactor) {
    // Create Box2D body for the projectile
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / scale, y / scale); // Convert to Box2D units
    body = world.CreateBody(&bodyDef);

    // Set up the projectile shape in Box2D
    b2CircleShape circleShape;
    circleShape.m_radius = radius / scale;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
   //probs removing
    fixtureDef.filter.categoryBits = 0x0002; // Projectiles category
    fixtureDef.filter.maskBits = 0x0004;    // Targets category

    body->CreateFixture(&fixtureDef);

    // Create SFML shape for rendering
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(radius, radius);  // Center the origin for proper rotation and placement
    shape.setPosition(x, y);

    // Set the velocity of the projectile in Box2D
    float velocityX = speed * std::cos(angle);
    float velocityY = speed * std::sin(angle);
    //body->SetLinearVelocity(b2Vec2(velocityX / scale, velocityY / scale));
    body->SetLinearVelocity(b2Vec2(0.0f, velocityY / scale));// Set the velocity in Box2D units
}

//Projectile::~Projectile() {
//    if (body != nullptr && body->GetWorld() != nullptr) {
//        body->GetWorld()->DestroyBody(body);  // Destroy the Box2D body
//        body = nullptr;                       // Nullify the pointer for safety
//    }
//}



// Update the projectile's position based on the Box2D physics simulation
void Projectile::update() {
    b2Vec2 position = body->GetPosition();
    shape.setPosition(position.x * scale, position.y * scale - 10.f);  // Convert to SFML units
}

// Draw the projectile on the SFML window
void Projectile::draw(sf::RenderWindow& window) {
    window.draw(shape);  // Render the projectile
}


// Get the current Box2D position of the projectile
b2Vec2 Projectile::getPosition() const {
    return body->GetPosition();
}
