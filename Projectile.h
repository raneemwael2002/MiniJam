#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Projectile {
public:
    float radius = 1;
    Projectile(b2World& world, float x, float y, float speed, float angle, float radius, float scaleFactor);

    void update();
    void draw(sf::RenderWindow& window);
    b2Vec2 getPosition() const;

private:

    b2Body* body;
    sf::CircleShape shape;
    float scale;
    sf::Texture texture;
    sf::Sprite sprite;
};
