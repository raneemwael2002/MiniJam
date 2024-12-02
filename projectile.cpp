#pragma once
#include "projectile.h"
#include <cmath>

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
    fixtureDef.density = 1.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    fixtureDef.filter.categoryBits = 0x0002; // Projectiles category
    fixtureDef.filter.maskBits = 0x0004;    // Targets category

    body->CreateFixture(&fixtureDef);

    
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(radius, radius);  
    shape.setPosition(x, y);

    
    float velocityX = speed * std::cos(angle);
    float velocityY = speed * std::sin(angle);
    body->SetLinearVelocity(b2Vec2(0.0f, velocityY / scale));
}

void Projectile::update() {
    b2Vec2 position = body->GetPosition();
    shape.setPosition(position.x * scale, position.y * scale - 10.f);  
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(shape);  
}



b2Vec2 Projectile::getPosition() const {
    return body->GetPosition();
}
