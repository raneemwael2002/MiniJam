//#pragma once
//#include <Box2D/Box2D.h>
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include "projectile.h"
//
//class Player {
//private:
//    b2Body* body;
//    sf::CircleShape shape;
//    float radius;
//    float scale;
//    float moveSpeed = 10.0f;
//    sf::Clock shootClock;
//
//public:
//    std::vector<Projectile> projectiles;
//    Player(b2World& world, float x, float y, float r, float scaleFactor = 0.4f);
//
//    ~Player();
//
//    void update();;
//    void handleInput(b2World& world);
//    void draw(sf::RenderWindow& window);
//
//    const std::vector<Projectile>& getProjectiles() const;
//    void clearProjectiles();
//    b2Vec2 getPosition() const;
//};