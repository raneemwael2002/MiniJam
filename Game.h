#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Taxi.h"
#include "TaxiTexture.h"
#include "Collectables.h"

class Game {
public:
    Game(sf::RenderWindow& window, const TaxiTexture& texture);
    void run();
    void update();
    void render(sf::RenderWindow& window);
    //void animateTaxis();
    void updateTaxis();
    void updateCollectables();
    void createTaxi();
    void helperTaxi();
    void updateHelperTaxi();
    void createCollectables();
    //void handleClick(sf::Event& event);
    Taxi *helperTaxiInstance;

private:
    sf::RenderWindow& window;
    std::vector<Taxi> taxies;
    std::vector<bool> isMoving;
    const TaxiTexture& texture;
    std::vector<Collectables> collectables; // Store collectables
    b2World world;                          // Box2D world
    sf::Clock clock;

    sf::Clock timer; // For measuring time intervals
   

    const float taxiSpeed = 1000.f; // Speed of the taxi movement (pixels per second)
    const float maxTimeInterval = 1.f;
    // Ground for collectables
    b2Body* groundBody;
    sf::RectangleShape ground;

    void setupGround();      
  
};
