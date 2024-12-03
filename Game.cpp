#include "Game.h"
#include <iostream>
#include <random>

Game::Game(sf::RenderWindow& window, const TaxiTexture& texture)
    : window(window), texture(texture) ,
world(b2Vec2(0.f, 9.8f)) { // Initialize Box2D world with gravity
    createTaxi();
    helperTaxi();
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
    if (clock.getElapsedTime().asSeconds() >= 2.f ) {
        createTaxi();
        createCollectables();
        clock.restart();
    }
}


void Game::update()
{
    updateTaxis();
    updateHelperTaxi();
    updateCollectables();
}


//void fallRandome() {
//
//};


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
    window.draw(helperTaxiInstance->sprite);
}


void Game::updateTaxis() {
    const float spacing = 50.f;
    const float verticalSpeed = 5.f;
    const float Margin = 200.f;

    for (size_t i = 0; i < taxies.size(); ++i) {
        sf::Vector2f position = taxies[i].getPosition();
        if (position.y <= 0) {
            if (i >-50) {
                sf::Vector2f prevPosition = taxies[i - 1].getPosition();

                if (prevPosition.x - spacing < Margin) {
                    position.x = window.getSize().x - Margin;
                }
                else {
                    position.x = prevPosition.x - spacing * 2;
                }
            }
            else {
                position.x = window.getSize().x - spacing * 4;
                position.y = -50;
            }
        }
        else {
            position.y -= verticalSpeed;
        }

        taxies[i].setPosition(position);
    }
}



void Game::createTaxi() {
    // Define positions for the taxis
    sf::Vector2f bottomRight(window.getSize().x - 200.f, window.getSize().y );
    sf::Vector2f bottomLeft(window.getSize().x - 600.f, window.getSize().y - 40.f);

    sf::Vector2f taxiSize(100.f, 50.f);

    Taxi rightTaxi(texture, bottomRight, taxiSize);
    taxies.push_back(rightTaxi);

    Taxi leftTaxi(texture, bottomLeft, taxiSize);
    taxies.push_back(leftTaxi);

}


void Game::helperTaxi() {
    // Initialize helper taxi at the top-right corner
    sf::Vector2f topRight(window.getSize().x, 200.f); // Start at the top-right corner
    sf::Vector2f taxiSize(100.f, 50.f);

    helperTaxiInstance= new Taxi (texture, topRight, taxiSize);
}

void Game::updateHelperTaxi() {
    // If the timer has exceeded the specified interval
    if (timer.getElapsedTime().asSeconds() >= maxTimeInterval) {
        // Reset the timer for the next interval
        timer.restart();

        // Move the helper taxi from right to left
        sf::Vector2f position = helperTaxiInstance->getPosition();

        // Move the taxi left (decrease the x position)
        position.x -= taxiSpeed * 0.1f;  // Adjust the speed of the taxi movement

        // If the taxi goes past the left side of the screen, reset its position to the right side
        if (position.x < -helperTaxiInstance->sprite.getGlobalBounds().width) {
            position.x = window.getSize().x;  // Reset position to top-right
        }

        // Update the taxi's position
        helperTaxiInstance->setPosition(position);
    }
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

//void Game::createCollectables() {
//    for (const auto& taxi : taxies) {
//        sf::Vector2f initialPosition = taxi.getPosition();
//        collectables.emplace_back(world, 5.f, initialPosition, sf::Color::Red);
//    }
//}

//void Game::handleClick(sf::Event& event) {
//    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
//        createCollectables(); // Create a collectable on Space key press
//    }
//}
