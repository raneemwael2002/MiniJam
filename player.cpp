#pragma once
#include "player.h"
#include"converter.h"
#include"projectile.h"
#include<iostream>

Player::Player(b2World& world, float x, float y, float r, float scaleFactor)
    : world(world), radius(r), scale(scaleFactor) {

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
    fixtureDef.restitution = 0.8f; 
    fixtureDef.filter.categoryBits = 0x0002; // Projectiles category
    fixtureDef.filter.maskBits = 0x0004;    // Targets category

    body->CreateFixture(&fixtureDef);

    
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(radius, radius); 
    shape.setPosition(x, y);
}

Player::~Player() {

    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
    for (Projectile& proj : projectiles) {
        proj.draw(window);
    }
}

b2Vec2 Player::getPosition() const {
    return body->GetPosition();
}

void Player::applyForce(const b2Vec2& force) {
    body->ApplyForceToCenter(force, true);
}


void Player::wallCollision(sf::RenderTarget* window) {
    b2Vec2 currentPosition = body->GetPosition();
    float radius = shape.getRadius();

    // Correcting boundary checks based on scale
    if (currentPosition.x - radius < 15.f / scale) {
        currentPosition.x = 15.f / scale + radius;
    }

    if (currentPosition.x + radius >= window->getSize().x / scale - 35.f / scale) {
        currentPosition.x = window->getSize().x / scale - radius - 35.f / scale;
    }

    if (currentPosition.y - radius < 15.f / scale) {
        currentPosition.y = 15.f / scale + radius;
    }

    if (currentPosition.y + radius > window->getSize().y / scale - 35.f / scale) {
        currentPosition.y = window->getSize().y / scale - radius - 35.f / scale;
    }

    body->SetTransform(currentPosition, body->GetAngle());

    // Updating shape position with proper scaling
    shape.setPosition(currentPosition.x * scale, currentPosition.y * scale);
}

void Player::shoot()
{
    static sf::Clock clock;
    std::cout << "Space pressed!" << std::endl;

    float cooldownTime = 0.3f;
    if (clock.getElapsedTime().asSeconds() > cooldownTime) {
        try {
            float speed = 10.0f;
            float angle = -90.f * (3.14f / 180.f); // Fixed upward angle
            projectiles.emplace_back(world, shape.getPosition().x, shape.getPosition().y, speed, angle, 5.f, scale);
            std::cout << "Projectile created successfully!" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error creating projectile: " << e.what() << std::endl;
        }
        clock.restart();
    }
}





void Player::update() {
    b2Vec2 position = body->GetPosition();
    shape.setPosition(position.x * scale, position.y * scale);
    shape.setRotation(body->GetAngle() * 180 / b2_pi);

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->update();
        if (it->getPosition().y < 0) { // Off-screen condition (e.g., above the screen)
            it = projectiles.erase(it); // Remove from vector
        }
        else {
            ++it;
        }
    }
}

    

void Player::handleInput() {
    b2Vec2 currentPosition = body->GetPosition();
    static sf::Clock clock;
    
    float moveSpeed = 0.1f;  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        currentPosition.x -= moveSpeed;
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        currentPosition.x += moveSpeed; // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        currentPosition.y -= moveSpeed; // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        currentPosition.y += moveSpeed; // Move down
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        std::cout << "Space pressed!" << std::endl;
        float cooldownTime = 0.3f;
        if (clock.getElapsedTime().asSeconds() > cooldownTime) {
            try {
                float speed = 10.0f;
                float angle = -90.f * (3.14f / 180.f); // Fixed upward angle
                projectiles.emplace_back(world, shape.getPosition().x, shape.getPosition().y, speed, angle, 5.f, scale);
                std::cout << "Projectile created successfully!" << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error creating projectile: " << e.what() << std::endl;
            }
            clock.restart();
        }
        
    }

    body->SetTransform(currentPosition, body->GetAngle());
}

