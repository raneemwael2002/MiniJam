//#pragma once
//#include <Box2D/Box2D.h>
//#include <SFML/Graphics.hpp>
//class Projectile {
//public:
//    Projectile(b2World& world, float x, float y, float speed, float angle, float radius, float scaleFactor);
//
//    void update();  // Update position based on velocity
//    void draw(sf::RenderWindow& window);  // Draw the projectile
//
//    b2Vec2 getPosition() const { return body->GetPosition(); }
//
//private:
//    b2Body* body;
//    sf::CircleShape shape;
//    float scale;
//};
//
//Projectile::Projectile(b2World& world, float x, float y, float speed, float angle, float radius, float scaleFactor)
//    : scale(scaleFactor) {
//    // Create Box2D body for the projectile
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(x / scale, y / scale); // Convert to Box2D units
//    body = world.CreateBody(&bodyDef);
//
//    // Set up the projectile shape
//    b2CircleShape circleShape;
//    circleShape.m_radius = radius / scale;
//
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &circleShape;
//    fixtureDef.density = 1.5f;
//    fixtureDef.friction = 0.3f;
//    fixtureDef.restitution = 0.8f;
//    body->CreateFixture(&fixtureDef);
//
//    // Create SFML shape for rendering
//    shape.setRadius(radius);
//    shape.setFillColor(sf::Color::Yellow);
//    shape.setOrigin(radius, radius);
//    shape.setPosition(x, y);
//
//    // Set the velocity of the projectile
//    float velocityX = speed * cos(angle);
//    float velocityY = speed * sin(angle);
//    body->SetLinearVelocity(b2Vec2(velocityX / scale, velocityY / scale)); // Set the velocity in Box2D units
//}
//
//void Projectile::update() {
//    b2Vec2 position = body->GetPosition();
//    shape.setPosition(position.x * scale, position.y * scale+10.f);  // Convert to SFML units
//
//}
//
//void Projectile::draw(sf::RenderWindow& window) {
//    window.draw(shape);  // Draw the projectile
//}


#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(b2World& world, float x, float y, float speed, float angle, float radius, float scaleFactor);
  //  ~Projectile();
    void update();  // Update position based on velocity
    void draw(sf::RenderWindow& window);  // Draw the projectile
    
    b2Vec2 getPosition() const;  // Return the Box2D position of the projectile

private:
    b2Body* body;             // Box2D body for physics
    sf::CircleShape shape;    // SFML shape for rendering
    float scale;              // Scale factor for unit conversion
};
