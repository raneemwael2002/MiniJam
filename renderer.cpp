#include "renderer.h"
#include <iostream>
void renderer::drawBackGround(sf::RenderWindow& window, float deltaTime) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/game_jam.jpg"))
    {
        std::cout << "Error loading textures!" << std::endl;
    }

   
    sf::Sprite background(backgroundTexture);
    float backgroundSpeed = -80.0f;
    static float background_y = 0;
    background_y = fmod(background_y - backgroundSpeed * deltaTime, backgroundTexture.getSize().y);
    background.setPosition(0,background_y);
    window.draw(background);
    background.setPosition(0,background_y - backgroundTexture.getSize().y);
    window.draw(background);
}


void renderer::drawPlayer(sf::RenderWindow& window, Player* player) {
    player->draw(window);
}

void renderer::drawTaxi(sf::RenderWindow& window, std::vector<Taxi>& taxies) {
    for (auto& taxi : taxies) {
        taxi.draw(window);
    }
}
