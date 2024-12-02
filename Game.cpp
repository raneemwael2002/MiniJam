#include "Game.h"
#include <iostream>
#include <random>

Game::Game(sf::RenderWindow& window)
    : window(window), world(b2Vec2(0.f, 9.8f)) { // Initialize Box2D world with gravity
    createTaxi();
    setupGround(); // Set up the ground for collectables
}

void Game::setupGround() {
    // Define the ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.f / 30.f, 600.f / 30.f);
    groundBody = world.CreateBody(&groundBodyDef);

    // Create a static ground fixture
    b2PolygonShape groundBox;
    groundBox.SetAsBox(400.f / 30.f, 10.f / 30.f);
    groundBody->CreateFixture(&groundBox, 0.f);

    // Set up the SFML ground rectangle for visual representation
    ground.setSize(sf::Vector2f(800.f, 20.f));
    ground.setPosition(0.f, 600.f);
    /*ground.setFillColor(sf::Color::Green);*/
}
void Game::run() {
    if (clock.getElapsedTime().asSeconds() >= 2.f && taxies.size() <= 30) {
        createTaxi();
        createCollectables();
        clock.restart();
    }
   
}


void Game::update()
{
    updateTaxis();
    updateCollectables();
}


   


void Game::render(sf::RenderWindow& window) {
    // Render taxis
    for (auto& taxi : taxies) {
        taxi.draw(window);
    }

    // Render collectables
    for (auto& collectable : collectables) {
        collectable.draw(window);
    }

    // Render ground
    window.draw(ground);
}

void Game::updateTaxis() {
    const float spacing = 50.f;
    const float lineHeight = 50.f;
    const float verticalSpeed = 5.f;
    const float leftMargin = 200.f;

    for (size_t i = 0; i < taxies.size(); ++i) {
        sf::Vector2f position = isMoving[i] ? taxies[i].getPosition()
            : sf::Vector2f(taxies[i].getPosition().x, (int)(i / 10) * 10 + 20);

        if (position.y <= (int)(i / 10) * 10 + 20) {
            isMoving[i] = false;
            if (i > 0) {
                sf::Vector2f prevPosition = taxies[i - 1].getPosition();

                if (prevPosition.x - spacing < leftMargin) {
                    position.x = window.getSize().x - spacing * 4;
                    position.y = prevPosition.y + lineHeight;
                }
                else {
                    position.x = prevPosition.x - spacing;
                    position.y = prevPosition.y;
                }
            }
            else {
                position.x = window.getSize().x - spacing * 4;
                position.y = (int)(i / 10) * 10 + 20;
            }
        }
        else {
            position.y -= verticalSpeed;
        }

        taxies[i].setPosition(position);
    }
}

void Game::createTaxi() {
    sf::Vector2f bottomRight(window.getSize().x - 200.f, window.getSize().y - 40.f);
    Taxi taxi(20.f, bottomRight, sf::Color::Yellow);
    taxies.push_back(taxi);
    isMoving.push_back(true);

    sf::Vector2f bottomLeft(window.getSize().x - 600.f, window.getSize().y - 40.f);
    Taxi leftTaxi(20.f, bottomLeft, sf::Color::Yellow);
    taxies.push_back(leftTaxi);
    isMoving.push_back(true);
}

void Game::updateCollectables() {
    // Update physics world
    world.Step(1.f / 60.f, 8, 3);

    // Update all collectables
    for (auto& collectable : collectables) {
        collectable.update();
    }
}

void Game::createCollectables() {
    // Create a new collectable at a random position near the top
    sf::Vector2f initialPosition(window.getSize().x / 2.f, 50.f);
    collectables.emplace_back(world, 5.f, initialPosition, sf::Color::Red);
}

void Game::handleClick(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        createCollectables(); // Create a collectable on Space key press
    }
}
