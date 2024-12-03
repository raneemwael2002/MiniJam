#include "TaxiTexture.h"
#include <iostream>

TaxiTexture::TaxiTexture() : loaded(false) {
    if (!texture.loadFromFile("Taxi0.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    else {
        loaded = true;
    }
}

const sf::Texture& TaxiTexture::getTexture() const {
    return texture;
}

bool TaxiTexture::isLoaded() const {
    return loaded;
}
