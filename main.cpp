#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include"Player.h"
#include"projectile.h"
#include<iostream>
const float SCALE = 4.0f; 

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 800), "Dynamic Ball Example");

    b2Vec2 gravity(0.f, 0.0f);
    b2World world(gravity);


   // Player player(world, 400.f, 300.f, 20.f, 30.f);
    Player player(world, window.getSize().x / 2.f, 750.f, 20.f, SCALE);

    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(400 / SCALE, 600 / SCALE); 
    b2Body* ground = world.CreateBody(&groundDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(400 / SCALE, 10 / SCALE); 
    ground->CreateFixture(&groundShape, 0.0f);

    
    sf::CircleShape ballShape(20.0f); 
    ballShape.setFillColor(sf::Color::Red); 
    ballShape.setOrigin(20.0f, 20.0f); 

    sf::RectangleShape groundRect;
    groundRect.setSize(sf::Vector2f(800, 60)); 
    groundRect.setOrigin(400, 10);
    groundRect.setPosition(ground->GetPosition().x * SCALE, ground->GetPosition().y * SCALE);
    groundRect.setFillColor(sf::Color::Green);

    
    
    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                player.shoot();
            }
        }

        float timeStep = 1.0f / 60.0f; // 60 FPS
        int32 velocityIterations = 8;
        int32 positionIterations = 3;
        world.Step(timeStep, velocityIterations, positionIterations);

        ballShape.setPosition(player.getPosition().x * SCALE, player.getPosition().y * SCALE);
       // ballShape.setRotation(ball->GetAngle() * 180 / b2_pi); // Rotation is optional here

        // Render
        window.clear();
      //  std::cout << player.getPosition().x <<" "<< player.getPosition().y<<std::endl;

       player.wallCollision(&window);
      //std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;

       player.handleInput();
       //std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;

        player.update();
        player.draw(window);
        window.draw(ballShape);
      
        window.display();
        
    }

    return 0;
}
