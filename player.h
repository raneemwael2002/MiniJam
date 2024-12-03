#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <Box2D/Box2D.h>
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<vector>
#include"projectile.h"
class Player {
private:
    b2World& world;
    b2Body* body;         
    sf::CircleShape shape; 
    float radius;         
    float scale;          
    float moveSpeed;
    sf::Vector2f velocity;
    std::vector <Projectile> projectiles;
public:
    
    Player(b2World& world, float x, float y, float r, float scaleFactor=4.0f);

    ~Player();

    void update();

    void draw(sf::RenderWindow& window);

    b2Vec2 getPosition() const;

    void applyForce(const b2Vec2& force);

    void handleInput(sf::Sound& sound);

    void wallCollision(sf::RenderTarget* target);

    void shoot();
};

#endif
