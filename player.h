#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Player {
private:
    b2Body* body;         
    sf::CircleShape shape; 
    float radius;         
    float scale;          
    float moveSpeed;
    sf::Vector2f velocity;
public:
    
    Player(b2World& world, float x, float y, float r, float scaleFactor=4.0f);

    ~Player();

    void update();

    void draw(sf::RenderWindow& window);

    b2Vec2 getPosition() const;

    void applyForce(const b2Vec2& force);

    void handleInput();

    void wallCollision(sf::RenderTarget* target);

    void shoot(b2Vec2 body);
};

#endif
