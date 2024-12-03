#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Taxi.h"
#include "Projectile.h"
#include <vector>

class renderer {
public:
    static void drawBackGround(sf::RenderWindow& window, float deltaTime);
    static void drawPlayer(sf::RenderWindow& window, Player* player);
    static void drawTaxi(sf::RenderWindow& window, std::vector<Taxi>& taxies);
};
